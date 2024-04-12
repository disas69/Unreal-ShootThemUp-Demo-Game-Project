// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/Services/STUChangeWeaponService.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Weapon/STUAIWeaponComponent.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (ChangeWeaponChance > 0 && FMath::FRand() <= ChangeWeaponChance)
    {
        const AAIController* Controller = OwnerComp.GetAIOwner();
        if (Controller != nullptr)
        {
            USTUAIWeaponComponent* WeaponComponent = FSTUUtils::GetActorComponent<USTUAIWeaponComponent>(Controller->GetPawn());
            if (WeaponComponent != nullptr)
            {
                WeaponComponent->TryEquipNextWeapon();
            }
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}