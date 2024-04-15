// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUPlayerStatsWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatsWidget::SetPlayerName(const FText& Text)
{
    PlayerNameText->SetText(Text);
}

void USTUPlayerStatsWidget::SetKills(const FText& Text)
{
    KillsText->SetText(Text);
}

void USTUPlayerStatsWidget::SetDeaths(const FText& Text)
{
    DeathsText->SetText(Text);
}

void USTUPlayerStatsWidget::SetTeamIcon(UTexture2D* Texture, const FLinearColor& Color)
{
    TeamIcon->SetBrushFromTexture(Texture);
    TeamIcon->SetColorAndOpacity(Color);
}

void USTUPlayerStatsWidget::SetPlayerIndicatorVisibility(bool bVisible)
{
    PlayerIndicatorImage->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}