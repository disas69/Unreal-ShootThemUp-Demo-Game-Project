// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUWeaponComponent.h"
#include "InputActionValue.h"
#include "Animation/AnimUtils.h"
#include "Animation/STUAnimationFinishedAnimNotify.h"
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

void USTUWeaponComponent::Initialize()
{
    SpawnWeapon();
    InitAnimations();

    if (Weapons.Num() > 0)
    {
        EquipWeapon(0);
    }
}

void USTUWeaponComponent::InitAnimations()
{
    // Subscribe to the equip animation finished event
    USTUAnimationFinishedAnimNotify* EquipFinishedNotify = FAnimUtils::FindAnimNotify<USTUAnimationFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify != nullptr)
    {
        EquipFinishedNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
    }

    for (const FWeaponData& Data : WeaponData)
    {
        if (Data.ReloadAnimation == nullptr)
        {
            continue;
        }

        // Subscribe to the reload animation finished event
        USTUAnimationFinishedAnimNotify* ReloadFinishedNotify = FAnimUtils::FindAnimNotify<USTUAnimationFinishedAnimNotify>(Data.ReloadAnimation);
        if (ReloadFinishedNotify != nullptr)
        {
            ReloadFinishedNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
        }
    }
}

void USTUWeaponComponent::StartFire()
{
    if (CanFire())
    {
        bIsFireInProgress = true;
        CurrentWeapon->StartFire();
    }
}

void USTUWeaponComponent::StopFire()
{
    bIsFireInProgress = false;

    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->StopFire();
    }
}

void USTUWeaponComponent::Aim(bool bAiming)
{
    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->Aim(bAiming);
    }
}

float USTUWeaponComponent::GetWeaponRecoil() const
{
    if (CurrentWeapon != nullptr)
    {
        return CurrentWeapon->GetRecoilValue();
    }

    return 0.0f;
}

void USTUWeaponComponent::Reload()
{
    if (CurrentWeapon != nullptr)
    {
        TryReload(CurrentWeapon);
    }
}

ASTUWeapon* USTUWeaponComponent::GetWeaponByType(TSubclassOf<ASTUWeapon> WeaponType) const
{
    for (ASTUWeapon* Weapon : Weapons)
    {
        if (Weapon != nullptr && Weapon->IsA(WeaponType))
        {
            return Weapon;
        }
    }

    return nullptr;
}

bool USTUWeaponComponent::AddAmmo(TSubclassOf<ASTUWeapon> WeaponType, int32 ClipsAmount)
{
    ASTUWeapon* Weapon = GetWeaponByType(WeaponType);
    if (Weapon != nullptr)
    {
        return Weapon->AddAmmo(ClipsAmount);
    }
    
    return false;
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
    if (WeaponData.Num() == 0 || Character == nullptr)
    {
        return;
    }

    FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
    SpawnParameters.Owner = Character;

    for (auto Data : WeaponData)
    {
        if (Data.WeaponClass == nullptr)
        {
            continue;
        }

        ASTUWeapon* Weapon = GetWorld()->SpawnActor<ASTUWeapon>(Data.WeaponClass, SpawnParameters);
        if (Weapon != nullptr)
        {
            Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::TryReload);
            Weapon->SetActorHiddenInGame(true);
            Weapons.Add(Weapon);
        }
    }
}

void USTUWeaponComponent::SwitchWeapon(const FInputActionValue& Value)
{
    if (CanEquip())
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
}

void USTUWeaponComponent::EquipWeapon(int32 NewWeaponIndex)
{
    bIsEquipInProgress = true;

    if (NewWeaponIndex < 0)
    {
        NewWeaponIndex = Weapons.Num() - 1;
    }
    else if (NewWeaponIndex >= Weapons.Num())
    {
        NewWeaponIndex = 0;
    }

    if (CurrentWeaponIndex == NewWeaponIndex)
    {
        bIsEquipInProgress = false;
        return;
    }

    HandlePreviousWeapon();
    CurrentWeaponIndex = NewWeaponIndex;

    ASTUWeapon* NewWeapon = Weapons[CurrentWeaponIndex];
    if (NewWeapon != nullptr)
    {
        NewWeapon->SetActorHiddenInGame(false);
        AttachWeaponToSocket(NewWeapon, WeaponEquippedSocketName);
        CurrentWeapon = NewWeapon;
        CurrentReloadAnimation = WeaponData[CurrentWeaponIndex].ReloadAnimation;
    }

    PlayAnimMontage(EquipAnimMontage);
}

int32 USTUWeaponComponent::GetNonEmptyWeaponIndex() const
{
    int32 Index = 0;
    for (const ASTUWeapon* Weapon : Weapons)
    {
        if (Weapon != nullptr && !Weapon->IsAmmoEmpty())
        {
            return Index;
        }

        Index++;
    }

    return Index;
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    if (MeshComp != Character->GetMesh())
    {
        return;
    }

    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->OnEquipFinished();
    }

    bIsEquipInProgress = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    if (MeshComp != Character->GetMesh())
    {
        return;
    }

    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->Reload();
    }
    
    bIsReloadInProgress = false;
}

void USTUWeaponComponent::HandlePreviousWeapon()
{
    if (PreviousWeaponIndex != -1)
    {
        // Reset the reloading state
        bIsReloadInProgress = false;

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
            CurrentWeapon->Aim(false);
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

bool USTUWeaponComponent::CanFire() const
{
    return CurrentWeapon != nullptr && !bIsEquipInProgress && !bIsReloadInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !bIsEquipInProgress;
}

bool USTUWeaponComponent::CanReload() const
{
    return CurrentWeapon != nullptr && CurrentWeapon->CanReload() && !bIsReloadInProgress;
}

void USTUWeaponComponent::TryReload(ASTUWeapon* EmptyWeapon)
{
    if (CurrentWeapon == EmptyWeapon)
    {
        if (CanReload())
        {
            if (CurrentWeapon->IsAmmoEmpty())
            {
                UE_LOG(LogTemp, Display, TEXT("Ammo is empty"));
            }
            else
            {
                StopFire();
                bIsReloadInProgress = true;
                PlayAnimMontage(CurrentReloadAnimation);
            }
        }
    }
    else
    {
        for (ASTUWeapon* Weapon : Weapons)
        {
            if (Weapon == EmptyWeapon)
            {
                Weapon->Reload();
            }
        }
    }
}
