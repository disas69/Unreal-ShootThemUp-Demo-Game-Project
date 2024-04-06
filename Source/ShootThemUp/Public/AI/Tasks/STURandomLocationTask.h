// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STURandomLocationTask.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTURandomLocationTask : public UBTTaskNode
{
    GENERATED_BODY()

public:
    USTURandomLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Radius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector TargetLocationKey;
};
