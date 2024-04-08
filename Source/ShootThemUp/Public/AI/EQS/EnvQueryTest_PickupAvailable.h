// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupAvailable.generated.h"

UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_PickupAvailable : public UEnvQueryTest
{
    GENERATED_BODY()

public:
    UEnvQueryTest_PickupAvailable(const FObjectInitializer& ObjectInitializer);

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
