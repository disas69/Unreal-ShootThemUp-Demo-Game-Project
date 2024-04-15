// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUPlayerHUDWidget.h"
#include "STUUtils.h"
#include "Components/ProgressBar.h"
#include "Components/STUHealthComponent.h"
#include "Weapon/STUWeapon.h"
#include "Weapon/STUWeaponComponent.h"

bool USTUPlayerHUDWidget::Initialize()
{
    const bool bInit = Super::Initialize();

    AController* PlayerController = GetOwningPlayer();
    if (PlayerController != nullptr)
    {
        PlayerController->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnPossessNewPawn);
    }

    OnPossessNewPawn(GetOwningPlayerPawn());
    
    return bInit;
}

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const USTUHealthComponent* HealthComponent = FSTUUtils::GetActorComponent<USTUHealthComponent>(GetOwningPlayerPawn());
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
    const USTUWeaponComponent* WeaponComponent = FSTUUtils::GetActorComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (WeaponComponent != nullptr)
    {
        return WeaponComponent->GetCurrentWeapon();
    }

    return nullptr;
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const USTUHealthComponent* HealthComponent = FSTUUtils::GetActorComponent<USTUHealthComponent>(GetOwningPlayerPawn());
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

void USTUPlayerHUDWidget::OnHealthChanged(float NewHealth, float HealthDelta)
{
    const float Percent = GetHealthPercent();
    HealthBar->SetPercent(Percent);
    HealthBar->SetFillColorAndOpacity(Percent > CriticalHealthThreshold ? NormalColor : CriticalColor);
    
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
}

void USTUPlayerHUDWidget::OnPossessNewPawn(APawn* Pawn)
{
    USTUHealthComponent* HealthComponent = FSTUUtils::GetActorComponent<USTUHealthComponent>(Pawn);
    if (HealthComponent != nullptr && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }

    if (HealthBar != nullptr)
    {
        HealthBar->SetPercent(GetHealthPercent());
    }
}
