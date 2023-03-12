// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURiffleWeapon.generated.h"

class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTURiffleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	
public:

    ASTURiffleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void MakeShot() override;

    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 10.0f;

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    USTUWeaponFXComponent* WeaponFXComponent;

private:
    FTimerHandle ShotTimerHandle;

    void MakeDamage(FHitResult& HitResult);
};
