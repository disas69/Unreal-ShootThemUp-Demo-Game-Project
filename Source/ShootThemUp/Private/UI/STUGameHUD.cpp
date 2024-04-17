// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUGameHUD.h"
#include "STUGameModeBase.h"
#include "UI/STUBaseWidget.h"

FVector2D ASTUGameHUD::GetCrossHairPosition() const
{
    FVector2D ViewportSize;
    GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
    const FVector2D Center(ViewportSize.X * 0.5f, ViewportSize.Y * 0.5f);
    return Center + CrossHairOffset;
}

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    CreateGameWidgets();

    ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode != nullptr)
    {
        GameMode->GameStateChanged.AddUObject(this, &ASTUGameHUD::OnGameStateChanged);
    }
}

void ASTUGameHUD::CreateGameWidgets()
{
    GameWidgets.Add(EGameState::Gameplay, CreateWidget<USTUBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EGameState::Pause, CreateWidget<USTUBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EGameState::Finished, CreateWidget<USTUBaseWidget>(GetWorld(), GameEndWidgetClass));

    for (const auto GameWidgetPair : GameWidgets)
    {
        USTUBaseWidget* GameWidget = GameWidgetPair.Value;
        if (GameWidget != nullptr)
        {
            GameWidget->AddToViewport();
            GameWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void ASTUGameHUD::DisplayGameWidget(EGameState NewState)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(NewState))
    {
        CurrentWidget = GameWidgets[NewState];
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->SetVisibility(ESlateVisibility::Visible);
            CurrentWidget->Show();
        }
    }
}

void ASTUGameHUD::OnGameStateChanged(EGameState NewState)
{
    DisplayGameWidget(NewState);
}

void ASTUGameHUD::DrawDebugCrossHair()
{
    const FVector2D Center = GetCrossHairPosition();

    constexpr float LineSize = 20.0f;
    constexpr float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::White;

    DrawLine(Center.X - LineSize / 2.0f, Center.Y, Center.X + LineSize / 2.0f, Center.Y, LineColor, LineThickness);
    DrawLine(Center.X, Center.Y - LineSize / 2.0f, Center.X, Center.Y + LineSize / 2.0f, LineColor, LineThickness);
}