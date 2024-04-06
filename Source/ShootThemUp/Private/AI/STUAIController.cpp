// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const ASTUAICharacter* AICharacter = Cast<ASTUAICharacter>(InPawn);
    if (AICharacter != nullptr)
    {
        RunBehaviorTree(AICharacter->BehaviorTree);
    }
}