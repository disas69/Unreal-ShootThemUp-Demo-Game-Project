// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/EQS/STUEnemyActorEnvQueryContext.h"
#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTUEnemyActorEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    Super::ProvideContext(QueryInstance, ContextData);

    const ASTUAICharacter* AICharacter = Cast<ASTUAICharacter>(QueryInstance.Owner.Get());
    if (AICharacter != nullptr)
    {
        const AAIController* AIController = Cast<AAIController>(AICharacter->GetController());
        if (AIController != nullptr)
        {
            const UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
            if (BlackboardComponent != nullptr)
            {
                UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKey)));
            }
        }
    }
}