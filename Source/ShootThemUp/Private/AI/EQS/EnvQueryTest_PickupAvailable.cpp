// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/EQS/EnvQueryTest_PickupAvailable.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUPickup.h"

UEnvQueryTest_PickupAvailable::UEnvQueryTest_PickupAvailable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupAvailable::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    const bool ExpectedValue = BoolValue.GetValue();
    
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const ASTUPickup* PickupActor = Cast<ASTUPickup>(ItemActor);

        if (PickupActor == nullptr)
        {
            continue;
        }

        It.SetScore(TestPurpose, FilterType, PickupActor->IsAvailable(), ExpectedValue);
    }
}