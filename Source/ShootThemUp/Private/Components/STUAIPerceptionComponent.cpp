// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
    const AAIController* Controller = Cast<AAIController>(GetOwner());
    if (Controller == nullptr)
    {
        return nullptr;
    }

    const APawn* ControlledPawn = Controller->GetPawn();
    if (ControlledPawn == nullptr)
    {
        return nullptr;
    }
    
    TArray<AActor*> PerceivedActors;
    GetCurrentlyPerceivedActors(nullptr, PerceivedActors);
    if (PerceivedActors.Num() == 0)
    {
        return nullptr;
    }

    AActor* ClosestEnemy = nullptr;
    float ClosestDistance = MAX_FLT;

    for (AActor* PerceivedActor : PerceivedActors)
    {
        APawn* PerceivedPawn = Cast<APawn>(PerceivedActor);
        if (PerceivedPawn == nullptr || !FSTUUtils::IsEnemy(Controller, PerceivedPawn->GetController()))
        {
            continue;
        }

        const USTUHealthComponent* HealthComponent = FSTUUtils::GetActorComponent<USTUHealthComponent>(PerceivedPawn);
        if (HealthComponent != nullptr && HealthComponent->IsAlive())
        {
            const float CurrentDistance = (PerceivedPawn->GetActorLocation() - ControlledPawn->GetActorLocation()).Size();
            if (CurrentDistance < ClosestDistance)
            {
                ClosestDistance = CurrentDistance;
                ClosestEnemy = PerceivedPawn;
            }
        }
    }

    return ClosestEnemy;
}
