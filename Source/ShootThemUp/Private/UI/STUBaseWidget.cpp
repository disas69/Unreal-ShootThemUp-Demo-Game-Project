// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUBaseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USTUBaseWidget::Show()
{
    PlayAnimation(ShowAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), ShowSound);
}