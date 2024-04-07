// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUWeaponComponent.h"
#include "STUAIWeaponComponent.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUAIWeaponComponent : public USTUWeaponComponent
{
    GENERATED_BODY()

public:
    void TryEquipNextWeapon();
    void TryEquipNonEmptyWeapon();
    
    virtual void StartFire() override;
    virtual void StopFire() override;
};
