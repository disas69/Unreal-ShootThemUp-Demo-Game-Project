// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SUTHealthAmountDecorator.generated.h"

UCLASS()
class SHOOTTHEMUP_API USUTHealthAmountDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    USUTHealthAmountDecorator();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = 0.0, ClampMax = 1.0))
    float AllowedHealthPercent = 0.6f;

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
