// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTURespawnComponent();

    void Respawn(float RespawnTime);
    float GetRespawnCountdown() const { return RespawnCountdown; }

private:
    float RespawnCountdown = 0.0f;
    FTimerHandle RespawnTimer;

    void RespawnTimerUpdate();
};
