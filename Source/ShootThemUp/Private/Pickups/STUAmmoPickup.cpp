// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Pickups/STUAmmoPickup.h"
#include "Weapon/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

bool ASTUAmmoPickup::TryCollectPickup(APawn* CollectorPawn)
{
    const USTUHealthComponent* HealthComponent = FSTUUtils::GetPlayerComponent<USTUHealthComponent>(CollectorPawn);
    if (HealthComponent == nullptr || !HealthComponent->IsAlive())
    {
        return false;
    }
    
    USTUWeaponComponent* WeaponComponent = FSTUUtils::GetPlayerComponent<USTUWeaponComponent>(CollectorPawn);
    if (WeaponComponent != nullptr)
    {
        return WeaponComponent->AddAmmo(WeaponType, ClipsAmount);
    }
    
    return false;
}