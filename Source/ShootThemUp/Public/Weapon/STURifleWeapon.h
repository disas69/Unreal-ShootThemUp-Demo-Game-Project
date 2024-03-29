// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUWeapon.h"
#include "STURifleWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void FireInternal() override;
private:
    FTimerHandle FireTimerHandle;
};
