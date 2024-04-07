// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/Decorators/STUHealthAmountDecorator.h"
#include "STUUtils.h"
#include "AIController.h"
#include "Components/STUHealthComponent.h"

USTUHealthAmountDecorator::USTUHealthAmountDecorator()
{
    NodeName = "Health Amount";
}

bool USTUHealthAmountDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    if (Controller != nullptr)
    {
        const USTUHealthComponent* HealthComponent = FSTUUtils::GetPlayerComponent<USTUHealthComponent>(Controller->GetPawn());
        if (HealthComponent != nullptr || !HealthComponent->IsAlive())
        {
            return HealthComponent->GetHealthPercent() < AllowedHealthPercent;
        }
    }
    
    return false;
}