// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUGameEndWidget.h"

#include "FSTUTextUtils.h"
#include "Components/VerticalBox.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatsWidget.h"

bool USTUGameEndWidget::Initialize()
{
    ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode)
    {
        GameMode->GameStateChanged.AddUObject(this, &USTUGameEndWidget::OnGameStateChange);
    }
    
    return Super::Initialize();
}

void USTUGameEndWidget::OnGameStateChange(EGameState NewState)
{
    if (NewState == EGameState::Finished)
    {
        DisplayPlayersStats();
    }
}

void USTUGameEndWidget::DisplayPlayersStats()
{
    PlayerStatsBox->ClearChildren();
    
    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const AController* Controller = It->Get();
        if (Controller != nullptr)
        {
            const ASTUPlayerState* PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
            if (PlayerState != nullptr)
            {
                USTUPlayerStatsWidget* UserWidget = CreateWidget<USTUPlayerStatsWidget>(GetWorld(), PlayerStatsWidgetClass);
                if (UserWidget != nullptr)
                {
                    UserWidget->SetPlayerName(FSTUTextUtils::TextFromString(PlayerState->GetPlayerName()));
                    UserWidget->SetKills(FSTUTextUtils::TextFromInt(PlayerState->GetKillsNum()));
                    UserWidget->SetDeaths(FSTUTextUtils::TextFromInt(PlayerState->GetDeathsNum()));
                    UserWidget->SetTeam(FSTUTextUtils::TextFromInt(PlayerState->GetTeamID()));
                    UserWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
                    PlayerStatsBox->AddChild(UserWidget);
                }
            }
        }
    }
}