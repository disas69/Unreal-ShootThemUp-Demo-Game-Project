// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Weapon/STUWeapon.h"
#include "Weapon/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const APawn* PlayerPawn = GetOwningPlayerPawn();
    if (PlayerPawn != nullptr)
    {
        const USTUHealthComponent* HealthComponent = PlayerPawn->FindComponentByClass<USTUHealthComponent>();
        if (HealthComponent != nullptr)
        {
            return HealthComponent->GetHealthPercent();
        }
    }

    return 0.0f;
}

ASTUWeapon* USTUPlayerHUDWidget::GetCurrentWeapon() const
{
    const APawn* PlayerPawn = GetOwningPlayerPawn();
    if (PlayerPawn != nullptr)
    {
        const USTUWeaponComponent* WeaponComponent = PlayerPawn->FindComponentByClass<USTUWeaponComponent>();
        if (WeaponComponent != nullptr)
        {
            return WeaponComponent->GetCurrentWeapon();
        }
    }

    return nullptr;
}
