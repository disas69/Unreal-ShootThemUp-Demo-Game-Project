// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"

USTURespawnComponent::USTURespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTURespawnComponent::Respawn(float RespawnTime)
{
    RespawnCountdown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void USTURespawnComponent::RespawnTimerUpdate()
{
    RespawnCountdown -= GetWorld()->GetTimerManager().GetTimerRate(RespawnTimer);
    if (RespawnCountdown <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimer);

        ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
        if (GameMode)
        {
            GameMode->Respawn(Cast<AController>(GetOwner()));
        }
    }
}
