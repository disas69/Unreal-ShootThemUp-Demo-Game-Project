// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/Decorators/STULevelBoundsDecorator.h"
#include "AIController.h"
#include "Player/STUBaseCharacter.h"

USTULevelBoundsDecorator::USTULevelBoundsDecorator()
{
    NodeName = "Level Bounds";
}

bool USTULevelBoundsDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    if (Controller != nullptr)
    {
        ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
        if (Character != nullptr)
        {
            return Character->GetInsideLevelBounds();
        }
    }

    return false;
}