// Shoot Them Up Game, All Rights Reserved


#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
    auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
    {
        const auto PlysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PlysMat))
        {
            Effect = EffectsMap[PlysMat];
        }
	}

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}