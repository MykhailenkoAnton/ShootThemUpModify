#pragma once
#include "STUCoreTypes.generated.h"

class ASTUBaseWeapon;
// weapon
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClimpEmptySignature, ASTUBaseWeapon*);
USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;
};


USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage* ReloadAnimMontage;
};

//USTRUCT(BlueprintType)
//struct WeaponUIdata
//{
//    GENERATED_USTRUCT_BODY()
//
//    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
//    UTexture2D* MainIcon;
//
//    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
//    UTexture2D* CrossHairIcor;
//};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;
};

//health
DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)