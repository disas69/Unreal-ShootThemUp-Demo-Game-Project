// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

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
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);

    if (PerceivedActors.Num() == 0)
    {
        return nullptr;
    }

    AActor* ClosestEnemy = nullptr;
    float ClosestDistance = MAX_FLT;

    for (AActor* PerceivedActor : PerceivedActors)
    {
        APawn* PerceivedPawn = Cast<APawn>(PerceivedActor);
        const USTUHealthComponent* HealthComponent = FSTUUtils::GetPlayerComponent<USTUHealthComponent>(PerceivedPawn);
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