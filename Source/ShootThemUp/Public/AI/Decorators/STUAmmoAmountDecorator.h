// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUAmmoAmountDecorator.generated.h"

class ASTUWeapon;

UCLASS()
class SHOOTTHEMUP_API USTUAmmoAmountDecorator : public UBTDecorator
{
    GENERATED_BODY()
public:
    USTUAmmoAmountDecorator();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASTUWeapon> WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    int32 AllowedClips = 1;

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
