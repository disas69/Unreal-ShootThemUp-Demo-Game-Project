// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

FString USTUGameDataWidget::GetTimerText() const
{
    return GetTimeFormattedText(GetRoundTime());
}

FString USTUGameDataWidget::GetRoundsText() const
{
    return FString::Printf(TEXT("Round: %i / %i"), GetCurrentRoundNum(), GetTotalRoundsNum());
}

FString USTUGameDataWidget::GetScoreText() const
{
    return FString::Printf(TEXT("Kills: %i"), GetKillsNum());
}

float USTUGameDataWidget::GetRoundTime() const
{
    const ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode != nullptr)
    {
        return GameMode->GetRoundCountdown();
    }

    return 0.0f;
}

int32 USTUGameDataWidget::GetCurrentRoundNum() const
{
    const ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode != nullptr)
    {
        return  GameMode->GetCurrentRoundNum();
    }

    return 0;
}

int32 USTUGameDataWidget::GetTotalRoundsNum() const
{
    const ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode != nullptr)
    {
        return  GameMode->GetTotalRoundsNum();
    }

    return 0;
}

int32 USTUGameDataWidget::GetKillsNum() const
{
    const AController* PlayerController = GetOwningPlayer();
    if (PlayerController != nullptr)
    {
        const ASTUPlayerState* PlayerState = PlayerController->GetPlayerState<ASTUPlayerState>();
        if (PlayerState != nullptr)
        {
            return PlayerState->GetKillsNum();
        }
    }

    return 0;
}

FString USTUGameDataWidget::GetTimeFormattedText(float TimeSeconds) const
{
    // Format time as MM:SS
    const int32 Minutes = FMath::FloorToInt(TimeSeconds / 60);
    const int32 Seconds = FMath::FloorToInt(TimeSeconds - Minutes * 60);
    return FString::Printf(TEXT("%02i:%02i"), Minutes, Seconds);
}