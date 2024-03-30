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

FString USTUPlayerHUDWidget::GetAmmoText() const
{
    ASTUWeapon* CurrentWeapon = GetCurrentWeapon();
    if (CurrentWeapon == nullptr)
    {
        return TEXT("0 / 0");
    }

    const FAmmoData& DefaultAmmo = CurrentWeapon->GetDefaultAmmoData();
    const FAmmoData& CurrentAmmo = CurrentWeapon->GetCurrentAmmoData();

    const FString BulletsString = FString::FromInt(CurrentAmmo.Bullets);
    const FString ClipsString = CurrentAmmo.bIsUnlimited ? TEXT("∞") : FString::FromInt(CurrentAmmo.Clips * DefaultAmmo.Bullets);

    return FString::Printf(TEXT("%s / %s"), *BulletsString, *ClipsString);
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
