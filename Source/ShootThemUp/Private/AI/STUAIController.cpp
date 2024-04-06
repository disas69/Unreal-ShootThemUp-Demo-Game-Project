// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController()
{
    STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*STUAIPerceptionComponent);
}

void ASTUAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* ClosestEnemy = STUAIPerceptionComponent->GetClosestEnemy();
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