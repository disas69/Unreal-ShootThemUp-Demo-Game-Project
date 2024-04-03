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
    ASTURifleWeapon();
    
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    USTUWeaponFXComponent* WeaponFXComponent = nullptr;

    UPROPERTY(EditAnywhere, Category = "VFX")
    UNiagaraSystem* TraceFX = nullptr;

    UPROPERTY(EditAnywhere, Category = "VFX")
    FString TraceTargetName = "TraceTarget";
    
    virtual void FireInternal() override;

private:
    FTimerHandle FireTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent = nullptr;

    void SetMuzzleFXActive(bool IsActive);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
};
