// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float Percent)
{
    HealthBar->SetPercent(Percent);
    HealthBar->SetFillColorAndOpacity(Percent > CriticalHealthThreshold ? NormalColor : CriticalColor);
}

void USTUHealthBarWidget::SetDistanceVisibility(float Distance)
{
    const float CurrentValue = HealthBar->GetPercent();
    const bool bVisible = Distance < DistanceVisibilityThreshold && CurrentValue > 0.0f && CurrentValue < ValueVisibilityThreshold;
    SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}