// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUWeaponComponent.h"

#include "InputActionValue.h"
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
void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    CurrentWeapon = nullptr;

    for (ASTUWeapon* Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }

    Weapons.Empty();
}

void USTUWeaponComponent::SpawnWeapon()
{
    if (WeaponClasses.Num() == 0 || Character == nullptr)
    {
        return;
    }

    FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
    SpawnParameters.Owner = Character;

    for (auto WeaponClass : WeaponClasses)
    {
        if (WeaponClass == nullptr)
        {
            continue;
        }

        ASTUWeapon* Weapon = GetWorld()->SpawnActor<ASTUWeapon>(WeaponClass, SpawnParameters);
        if (Weapon != nullptr)
        {
            Weapon->SetActorHiddenInGame(true);
            Weapons.Add(Weapon);
        }
    }

    if (Weapons.Num() > 0)
    {
        EquipWeapon(0);
    }
}

void USTUWeaponComponent::SwitchWeapon(const FInputActionValue& Value)
{
    const float Index = Value.Get<float>();
    if (Index > 0)
    {
        EquipWeapon(CurrentWeaponIndex + 1);
    }
    else if (Index < 0)
    {
        EquipWeapon(CurrentWeaponIndex - 1);
    }
}

void USTUWeaponComponent::EquipWeapon(int32 NewWeaponIndex)
{
    if (NewWeaponIndex < 0)
    {
        NewWeaponIndex = Weapons.Num() - 1;
    }
    else if (NewWeaponIndex >= Weapons.Num())
    {
        NewWeaponIndex = 0;
    }

    HandlePreviousWeapon();
    CurrentWeaponIndex = NewWeaponIndex;

    ASTUWeapon* NewWeapon = Weapons[CurrentWeaponIndex];
    if (NewWeapon != nullptr)
    {
        NewWeapon->SetActorHiddenInGame(false);
        AttachWeaponToSocket(NewWeapon, WeaponEquippedSocketName);
        CurrentWeapon = NewWeapon;
    }

    PlayAnimMontage(EquipAnimMontage);

    UE_LOG(LogTemp, Display, TEXT("Equipped weapon: %s"), *CurrentWeapon->GetName());
}

void USTUWeaponComponent::HandlePreviousWeapon()
{
    if (PreviousWeaponIndex != -1)
    {
        // Hide the previous weapon
        ASTUWeapon* PreviousWeapon = Weapons[PreviousWeaponIndex];
        if (PreviousWeapon != nullptr)
        {
            PreviousWeapon->SetActorHiddenInGame(true);
        }

        // Attach the current weapon to the armory socket
        PreviousWeaponIndex = CurrentWeaponIndex;
        if (CurrentWeapon != nullptr)
        {
            CurrentWeapon->StopFire();
            CurrentWeapon->SetActorHiddenInGame(false);
            AttachWeaponToSocket(CurrentWeapon, WeaponArmorySocketName);
        }
    }
    else
    {
        // Attach a first available second weapon to the armory socket
        if (Weapons.Num() > 1)
        {
            PreviousWeaponIndex = 1;
            ASTUWeapon* NextWeapon = Weapons[PreviousWeaponIndex];
            if (NextWeapon != nullptr)
            {
                NextWeapon->SetActorHiddenInGame(false);
                AttachWeaponToSocket(NextWeapon, WeaponArmorySocketName);
            }
        }
    }
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUWeapon* Weapon, const FName& SocketName) const
{
    Weapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
    Character->PlayAnimMontage(AnimMontage);
}