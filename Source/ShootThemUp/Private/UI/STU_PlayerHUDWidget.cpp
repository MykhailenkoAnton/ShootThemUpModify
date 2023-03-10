// Shoot Them Up Game, All Rights Reserved


#include "UI/STU_PlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"


float USTU_PlayerHUDWidget::GetHealthPercent() const
{
    
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;
    
    return HealthComponent->GetHealthPercent();
}

bool USTU_PlayerHUDWidget::GeCurrenttWeaponUIData(FWeaponUIData& UIData) const 
{
    
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GeCurrenttWeaponUIData(UIData);
}

bool USTU_PlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const 
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USTU_PlayerHUDWidget::IsPlayerAlive() const 
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());

    return HealthComponent && !HealthComponent->IsDead();
}

bool USTU_PlayerHUDWidget::IsPlayerSpectating() const 
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}
