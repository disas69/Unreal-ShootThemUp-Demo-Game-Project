// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUAIWeaponComponent.h"
#include "Weapon/STUWeapon.h"

void USTUAIWeaponComponent::TryEquipNextWeapon()
{
    EquipWeapon(GetCurrentWeaponIndex() + 1);
}

void USTUAIWeaponComponent::TryEquipNonEmptyWeapon()
{
    const int32 NextWeaponIndex = GetNonEmptyWeaponIndex();
    EquipWeapon(NextWeaponIndex);
}

void USTUAIWeaponComponent::StartFire()
{
    if (CurrentWeapon != nullptr && CurrentWeapon->IsAmmoEmpty())
    {
        TryEquipNonEmptyWeapon();
    }
    
    Super::StartFire();
}

void USTUAIWeaponComponent::StopFire()
{
    Super::StopFire();
}
