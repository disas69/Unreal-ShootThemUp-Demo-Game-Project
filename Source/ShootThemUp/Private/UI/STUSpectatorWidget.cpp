// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUSpectatorWidget.h"
#include "FSTUTextUtils.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

FString USTUSpectatorWidget::GetRespawnCountdownText() const
{
    return FSTUTextUtils::FormatTime(GetRespawnCountdown());
}

float USTUSpectatorWidget::GetRespawnCountdown() const
{
    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController != nullptr)
    {
        const USTURespawnComponent* RespawnComponent = FSTUUtils::GetActorComponent<USTURespawnComponent>(PlayerController);
        if (RespawnComponent != nullptr)
        {
            return RespawnComponent->GetRespawnCountdown();
        }
    }

    return 0.0f;
}