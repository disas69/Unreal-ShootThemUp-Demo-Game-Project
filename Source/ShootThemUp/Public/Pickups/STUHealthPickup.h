// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUPickup.h"
#include "STUHealthPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUPickup
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = 1.0f, ClampMax = 100.0f))
    float HealthAmount = 100.0f;

protected:
    virtual bool TryCollectPickup(APawn* CollectorPawn) override;
};
