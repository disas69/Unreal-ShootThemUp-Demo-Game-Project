// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUGameEndWidget.h"
#include "FSTUTextUtils.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUPlayerState.h"
#include "UI/STUButtonWidget.h"
#include "UI/STUPlayerStatsWidget.h"

bool USTUGameEndWidget::Initialize()
{
    const bool bInit = Super::Initialize();
    return bInit;
}

void USTUGameEndWidget::SetVisibility(ESlateVisibility InVisibility)
{
    Super::SetVisibility(InVisibility);

    if (InVisibility == ESlateVisibility::Visible)
    {
        RestartButton->SetFocus(true);
    }
}

void USTUGameEndWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (RestartButton != nullptr && RestartButton->Get() != nullptr)
    {
        RestartButton->Get()->OnClicked.AddDynamic(this, &USTUGameEndWidget::RestartLevel);
    }

    if (ExitButton != nullptr && ExitButton->Get() != nullptr)
    {
        ExitButton->Get()->OnClicked.AddDynamic(this, &USTUGameEndWidget::ExitLevel);
    }

    ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode)
    {
        GameMode->GameStateChanged.AddUObject(this, &USTUGameEndWidget::OnGameStateChange);
    }
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

    TArray<const ASTUPlayerState*> PlayerStates;
    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const AController* Controller = It->Get();
        if (Controller != nullptr)
        {
            const ASTUPlayerState* PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
            if (PlayerState != nullptr)
            {
                PlayerStates.Add(PlayerState);
            }
        }
    }

    // Sort by kills
    PlayerStates.Sort([](const ASTUPlayerState& A, const ASTUPlayerState& B) { return A.GetKillsNum() > B.GetKillsNum(); });

    for (const ASTUPlayerState* PlayerState : PlayerStates)
    {
        USTUPlayerStatsWidget* PlayerStatWidget = CreateWidget<USTUPlayerStatsWidget>(GetWorld(), PlayerStatsWidgetClass);
        if (PlayerStatWidget)
        {
            USTUPlayerStatsWidget* UserWidget = CreateWidget<USTUPlayerStatsWidget>(GetWorld(), PlayerStatsWidgetClass);
            if (UserWidget != nullptr)
            {
                UserWidget->SetPlayerName(FSTUTextUtils::TextFromString(PlayerState->GetPlayerName()));
                UserWidget->SetKills(FSTUTextUtils::TextFromInt(PlayerState->GetKillsNum()));
                UserWidget->SetDeaths(FSTUTextUtils::TextFromInt(PlayerState->GetDeathsNum()));
                UserWidget->SetTeamIcon(PlayerState->GetTeamData().Icon, PlayerState->GetTeamData().Color);
                UserWidget->SetPlayerIndicatorVisibility(PlayerState->GetPlayerController() != nullptr);
                PlayerStatsBox->AddChild(UserWidget);
            }
        }
    }
}

void USTUGameEndWidget::RestartLevel()
{
    const FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevel));
}

void USTUGameEndWidget::ExitLevel()
{
    USTUGameInstance* GameInstance = GetGameInstance<USTUGameInstance>();
    if (GameInstance != nullptr)
    {
        GameInstance->OpenMenuLevel();
    }
}