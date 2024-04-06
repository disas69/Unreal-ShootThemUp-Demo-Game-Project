// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/Services/STUFireWeaponService.h"
#include "AIController.h"
#include "STUUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Weapon/STUWeaponComponent.h"

USTUFireWeaponService::USTUFireWeaponService()
{
    NodeName = "Fire Weapon";
}

void USTUFireWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    if (Controller != nullptr)
    {
        const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
        if (BlackboardComponent != nullptr)
        {
            const bool bHasTarget = BlackboardComponent->GetValueAsObject(EnemyActorKey.SelectedKeyName) != nullptr;
            USTUWeaponComponent* WeaponComponent = FSTUUtils::GetPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

            if (WeaponComponent != nullptr)
            {
                if (bHasTarget)
                {
                    WeaponComponent->StartFire();
                }
                else
                {
                    WeaponComponent->StopFire();
                }
            }
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}