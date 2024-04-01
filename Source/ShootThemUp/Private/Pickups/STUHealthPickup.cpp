// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

bool ASTUHealthPickup::TryCollectPickup(APawn* CollectorPawn)
{
    USTUHealthComponent* HealthComponent = FSTUUtils::GetPlayerComponent<USTUHealthComponent>(CollectorPawn);
    if (HealthComponent == nullptr || !HealthComponent->IsAlive())
    {
        return false;
    }
    
    return HealthComponent->AddHealth(HealthAmount);
}