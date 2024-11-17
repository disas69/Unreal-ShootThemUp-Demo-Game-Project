// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUDamageTextWidget.h"
#include "FSTUTextUtils.h"
#include "Components/TextBlock.h"

void USTUDamageTextWidget::SetDamageText(const FString& Text) const
{
    DamageText->SetText(FSTUTextUtils::TextFromString(Text));
}

void USTUDamageTextWidget::Show(bool bAnimate)
{
    Super::Show(bAnimate);

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USTUDamageTextWidget::RemoveFromParent, LifeTime);
}