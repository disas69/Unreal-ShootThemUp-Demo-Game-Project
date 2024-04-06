// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUAIWeaponComponent.h"
#include "Weapon/STUWeapon.h"

void USTUAIWeaponComponent::StartFire()
{
    TrySwitchEmptyWeapon();
    Super::StartFire();
}

void USTUAIWeaponComponent::StopFire()
{
    Super::StopFire();
    TrySwitchEmptyWeapon();
}

void USTUAIWeaponComponent::TrySwitchEmptyWeapon()
{
    if (CurrentWeapon != nullptr && CurrentWeapon->IsAmmoEmpty())
    {
        const int32 NextWeaponIndex = GetNonEmptyWeaponIndex();
        EquipWeapon(NextWeaponIndex);
    }
}
