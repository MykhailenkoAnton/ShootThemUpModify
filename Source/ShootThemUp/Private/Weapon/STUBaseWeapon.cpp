// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All);

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeapoMesh");
    SetRootComponent(WeaponMesh);

}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    check(WeaponMesh);
    CurrentAmmo = DefaultAmmo;
}

void ASTUBaseWeapon::StartFire()
{

}

void ASTUBaseWeapon::StopFire()
{

}

void ASTUBaseWeapon::MakeShot()
{

}

APlayerController* ASTUBaseWeapon::GetPlayerContoller() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotator) const 
{
    const auto Controller = GetPlayerContoller();
    if (!Controller) return false;

    
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotator);
    return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const 
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const 
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::DecreaseAmmo() 
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(BaseWeaponLog, Warning, TEXT("Clip is empty."));
        return;
    }

    CurrentAmmo.Bullets--;

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClimpEmpty.Broadcast(this);
    }
}

bool ASTUBaseWeapon::IsAmmoEmpty() const 
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const 
{
    return CurrentAmmo.Bullets == 0;
}

void ASTUBaseWeapon::ChangeClip() 
{
    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            UE_LOG(BaseWeaponLog, Warning, TEXT("No more clips."));
            return;
        }
        CurrentAmmo.Clips--;
    }
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(BaseWeaponLog, Display, TEXT("---- CHANGE CLIP ----"));
}

void ASTUBaseWeapon::LogAmmo() 
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(BaseWeaponLog, Display, TEXT("%s"), *AmmoInfo);
}

bool ASTUBaseWeapon::CanReload() const 
{
    return (CurrentAmmo.Bullets < DefaultAmmo.Bullets) && (CurrentAmmo.Clips > 0);
}

bool ASTUBaseWeapon::IsAmmoFull() const 
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool ASTUBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
    if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

    if (IsAmmoEmpty())
    {
        UE_LOG(BaseWeaponLog, Display, TEXT("Ammo was empty"));
        CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClimpEmpty.Broadcast(this);
    }
    else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if (DefaultAmmo.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmo.Clips = NextClipsAmount;
            UE_LOG(BaseWeaponLog, Display, TEXT("Clips were added"));
        }
        else
        {
            CurrentAmmo.Clips = DefaultAmmo.Clips;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
            UE_LOG(BaseWeaponLog, Display, TEXT("Ammo is full now"));
        }
    }
    else
    {
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        UE_LOG(BaseWeaponLog, Display, TEXT("Bullet were added"));
    }
    
    return true;
}
