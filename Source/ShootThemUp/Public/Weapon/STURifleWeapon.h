// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void Aim(bool bAiming) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
    float AimCameraFOV = 60.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
    float AimSensitivity = 0.6f;
    
    virtual void FireInternal() override;

private:
    FTimerHandle FireTimerHandle;
};
