// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUPickup.h"
#include "STUHealthPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUPickup
{
    GENERATED_BODY()

protected:
    virtual bool TryCollectPickup(APawn* CollectorPawn) override;
};
