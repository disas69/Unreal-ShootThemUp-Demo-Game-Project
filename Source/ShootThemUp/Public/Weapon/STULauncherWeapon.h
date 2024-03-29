// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;

UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTUProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 200.0f;
    
    virtual void FireInternal() override;
};
