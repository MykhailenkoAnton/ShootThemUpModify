// Shoot Them Up Game, All Rights Reserved


#include "UI/STU_PlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"


float USTU_PlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return 0.0f;

    const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
    const auto HealthComponent = Cast<USTUHealthComponent>(Component);
    if (!HealthComponent) return 0.0f;
    
    return HealthComponent->GetHealthPercent();
}

bool USTU_PlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const 
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return false;

    const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
    const auto WeaponthComponent = Cast<USTUWeaponComponent>(Component);
    if (!WeaponthComponent) return false;

    return WeaponthComponent->GetWeaponUIData(UIData);
}