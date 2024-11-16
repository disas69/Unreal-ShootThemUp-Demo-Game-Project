// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pickups/STUAmmoPickup.h"
#include "STUWeaponComponent.generated.h"

struct FWeaponImageData;
struct FInputActionValue;
class ASTUBaseCharacter;
class ASTUWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TSubclassOf<ASTUWeapon> WeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    UAnimMontage* ReloadAnimation = nullptr;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponComponent();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    FName WeaponEquippedSocketName = "WeaponSocket";

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    UAnimMontage* EquipAnimMontage = nullptr;

    void Initialize();
    
    UFUNCTION()
    void Reload();

    UFUNCTION()
    void SwitchWeapon(const FInputActionValue& Value);

    bool IsFireInProgress() const { return bIsFireInProgress; }
    int32 GetCurrentWeaponIndex() const { return CurrentWeaponIndex; }
    ASTUWeapon* GetCurrentWeapon() const { return CurrentWeapon; }
    ASTUWeapon* GetWeaponByType(TSubclassOf<ASTUWeapon> WeaponType) const;

    bool AddAmmo(TSubclassOf<ASTUWeapon> WeaponType, int32 ClipsAmount);
    void Aim(bool bAiming);
    float GetWeaponRecoil() const;

    virtual void StartFire();
    virtual void StopFire();
    
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
    UPROPERTY()
    ASTUBaseCharacter* Character = nullptr;

    UPROPERTY()
    ASTUWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    UAnimMontage* CurrentReloadAnimation = nullptr;

    UPROPERTY()
    TArray<ASTUWeapon*> Weapons = {};
    
    virtual void BeginPlay() override;

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;
    void EquipWeapon(int32 WeaponIndex);
    int32 GetNonEmptyWeaponIndex() const;

private:
    int32 CurrentWeaponIndex = -1;
    int32 PreviousWeaponIndex = -1;
    bool bIsFireInProgress = false;
    bool bIsEquipInProgress = false;
    bool bIsReloadInProgress = false;

    void SpawnWeapon();
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);
    void HandlePreviousWeapon();
    void AttachWeaponToSocket(ASTUWeapon* Weapon, const FName& SocketName) const;
    void PlayAnimMontage(UAnimMontage* AnimMontage) const;
    void TryReload(ASTUWeapon* EmptyWeapon);
};
