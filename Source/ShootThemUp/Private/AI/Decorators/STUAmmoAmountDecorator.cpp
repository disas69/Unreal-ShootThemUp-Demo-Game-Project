// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/Decorators/STUAmmoAmountDecorator.h"
#include "STUUtils.h"
#include "AIController.h"
#include "Components/STUHealthComponent.h"
#include "Weapon/STUWeapon.h"
#include "Weapon/STUWeaponComponent.h"

USTUAmmoAmountDecorator::USTUAmmoAmountDecorator()
{
    NodeName = "Ammo Amount";
}

bool USTUAmmoAmountDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    if (Controller != nullptr)
    {
        const USTUHealthComponent* HealthComponent = FSTUUtils::GetActorComponent<USTUHealthComponent>(Controller->GetPawn());
        if (HealthComponent != nullptr || !HealthComponent->IsAlive())
        {
            const USTUWeaponComponent* WeaponComponent = FSTUUtils::GetActorComponent<USTUWeaponComponent>(Controller->GetPawn());
            if (WeaponComponent != nullptr)
            {
                ASTUWeapon* Weapon = WeaponComponent->GetWeaponByType(WeaponType);
                if (Weapon != nullptr)
                {
                    return !Weapon->GetCurrentAmmoData().bIsUnlimited && Weapon->GetCurrentAmmoData().Clips < AllowedClips;
                }
            }
        }
    }
    
    return false;
}