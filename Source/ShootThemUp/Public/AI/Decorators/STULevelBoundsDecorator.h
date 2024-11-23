// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STULevelBoundsDecorator.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTULevelBoundsDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    USTULevelBoundsDecorator();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
