// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUWeaponComponent.h"
#include "Player/STUBaseCharacter.h"
#include "Weapon/STUWeapon.h"

USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    Character = Cast<ASTUBaseCharacter>(GetOwner());
}

void USTUWeaponComponent::StartFire()
{
    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->StartFire();
    }
}

void USTUWeaponComponent::StopFire()
{
    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->StopFire();
    }
}

void USTUWeaponComponent::SpawnWeapon()
{
    if (WeaponClass == nullptr || Character == nullptr)
    {
        return;
    }

    FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
    SpawnParameters.Owner = Character;
    
    CurrentWeapon = GetWorld()->SpawnActor<ASTUWeapon>(WeaponClass, SpawnParameters);
    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
    }
}
