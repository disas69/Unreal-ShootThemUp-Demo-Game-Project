// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseCharacter;
class ASTUWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponComponent();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TSubclassOf<ASTUWeapon> WeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    FName WeaponSocketName = "WeaponSocket";

    void SpawnWeapon();

    UFUNCTION()
    void Fire();

protected:
    UPROPERTY()
    ASTUBaseCharacter* Character = nullptr;

    UPROPERTY()
    ASTUWeapon* CurrentWeapon = nullptr;
    
    virtual void BeginPlay() override;

};
