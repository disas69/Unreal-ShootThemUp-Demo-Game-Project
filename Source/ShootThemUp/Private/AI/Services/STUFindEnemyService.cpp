// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/Services/STUFindEnemyService.h"
#include "AIController.h"
#include "STUUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUAIPerceptionComponent.h"

USTUFindEnemyService::USTUFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    if (Controller != nullptr)
    {
        UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
        const USTUAIPerceptionComponent* PerceptionComponent = FSTUUtils::GetPlayerComponent<USTUAIPerceptionComponent>(Controller);
    
        if (BlackboardComponent != nullptr && PerceptionComponent != nullptr)
        {
            BlackboardComponent->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}