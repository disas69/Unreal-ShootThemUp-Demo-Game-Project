// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUChangeWeaponService.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUChangeWeaponService : public UBTService
{
    GENERATED_BODY()

public:
    USTUChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = 0.0, ClampMax = 1.0))
    float ChangeWeaponChance = 0.3f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
