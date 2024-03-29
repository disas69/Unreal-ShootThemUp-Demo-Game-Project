// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

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
    
    void SpawnWeapon();
    void SwitchWeapon(const FInputActionValue& Value);

    UFUNCTION()
    void StartFire();

    UFUNCTION()
    void StopFire();
    
    UFUNCTION()
    void Reload();

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

private:
    int32 CurrentWeaponIndex = -1;
    int32 PreviousWeaponIndex = -1;
    bool bIsEquipInProgress = false;
    bool bIsReloadInProgress = false;
    
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void EquipWeapon(int32 WeaponIndex);
    void HandlePreviousWeapon();
    void AttachWeaponToSocket(ASTUWeapon* Weapon, const FName& SocketName) const;
    void PlayAnimMontage(UAnimMontage* AnimMontage) const;
    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;
};
