// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/Decorators/SUTHealthAmountDecorator.h"
#include "STUUtils.h"
#include "AIController.h"
#include "Components/STUHealthComponent.h"

USUTHealthAmountDecorator::USUTHealthAmountDecorator()
{
    NodeName = "Health Amount";
}

bool USUTHealthAmountDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    if (Controller != nullptr)
    {
        const USTUHealthComponent* HealthComponent = FSTUUtils::GetPlayerComponent<USTUHealthComponent>(Controller->GetPawn());
        if (HealthComponent != nullptr || !HealthComponent->IsAlive())
        {
            return HealthComponent->GetHealthPercent() <= AllowedHealthPercent;
        }
    }
    
    return false;
}