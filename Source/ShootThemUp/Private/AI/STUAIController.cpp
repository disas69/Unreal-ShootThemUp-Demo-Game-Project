// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController()
{
    STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*STUAIPerceptionComponent);
}

void ASTUAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* ClosestEnemy = GetClosestEnemy();
    if (ClosestEnemy != nullptr)
    {
        SetFocus(ClosestEnemy);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
    }
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const ASTUAICharacter* AICharacter = Cast<ASTUAICharacter>(InPawn);
    if (AICharacter != nullptr)
    {
        RunBehaviorTree(AICharacter->BehaviorTree);
    }
}

AActor* ASTUAIController::GetClosestEnemy() const
{
    const UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
    if (BlackboardComponent == nullptr)
    {
        return nullptr;
    }

    AActor* ClosestEnemy = Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKey));
    return ClosestEnemy;
}