// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUBaseWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USTUBaseWidget::Show(bool bAnimate)
{
    if (bAnimate)
    {
        PlayAnimation(ShowAnimation);
    }
    else
    {
        SetVisibility(ESlateVisibility::Visible);

        // Set animation to the last key frame
        if (ShowAnimation != nullptr)
        {
            float EndTime = ShowAnimation->GetEndTime();
            PlayAnimation(ShowAnimation, EndTime, 1, EUMGSequencePlayMode::Forward, 1);
        }
    }

    if (ShowSound)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), ShowSound);
    }
}