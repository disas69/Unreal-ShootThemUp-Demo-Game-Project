// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/Tasks/STUEnemyLocationTask.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

USTUEnemyLocationTask::USTUEnemyLocationTask()
{
    NodeName = "Select Enemy Location";
}

EBTNodeResult::Type USTUEnemyLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

    if (Controller == nullptr || Blackboard == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    APawn* Pawn = Controller->GetPawn();
    if (Pawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
    if (NavSystem == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    const AActor* EnemyActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));
    if (EnemyActor == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    FNavLocation NavLocation;
    if (NavSystem->GetRandomReachablePointInRadius(EnemyActor->GetActorLocation(), Radius, NavLocation))
    {
        Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, NavLocation.Location);
        return EBTNodeResult::Succeeded;
    }
    
    return EBTNodeResult::Failed;
}