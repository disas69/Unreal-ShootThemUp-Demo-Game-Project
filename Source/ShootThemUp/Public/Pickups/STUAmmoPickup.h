// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUPickup.h"
#include "STUAmmoPickup.generated.h"

class ASTUWeapon;

UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUPickup
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = 1, ClampMax = 10))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ASTUWeapon> WeaponType;

protected:
    virtual bool TryCollectPickup(APawn* CollectorPawn) override;
};
