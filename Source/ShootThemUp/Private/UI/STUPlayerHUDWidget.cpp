// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Weapon/STUWeapon.h"
#include "Weapon/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const USTUHealthComponent* HealthComponent = GetHealthComponent();
    if (HealthComponent != nullptr)
    {
        return HealthComponent->GetHealthPercent();
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
    const USTUWeaponComponent* WeaponComponent = GetWeaponComponent();
    if (WeaponComponent != nullptr)
    {
        return WeaponComponent->GetCurrentWeapon();
    }

    return nullptr;
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const USTUHealthComponent* HealthComponent = GetHealthComponent();
    if (HealthComponent != nullptr)
    {
        return HealthComponent->IsAlive();
    }

    return false;
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const AController* PlayerController = GetOwningPlayer();
    if (PlayerController != nullptr)
    {
        return PlayerController->GetStateName() == NAME_Spectating;
    }

    return false;
}

USTUHealthComponent* USTUPlayerHUDWidget::GetHealthComponent() const
{
    const APawn* PlayerPawn = GetOwningPlayerPawn();
    if (PlayerPawn != nullptr)
    {
        return PlayerPawn->FindComponentByClass<USTUHealthComponent>();
    }

    return nullptr;
}

USTUWeaponComponent* USTUPlayerHUDWidget::GetWeaponComponent() const
{
    const APawn* PlayerPawn = GetOwningPlayerPawn();
    if (PlayerPawn != nullptr)
    {
        return PlayerPawn->FindComponentByClass<USTUWeaponComponent>();
    }

    return nullptr;
}
