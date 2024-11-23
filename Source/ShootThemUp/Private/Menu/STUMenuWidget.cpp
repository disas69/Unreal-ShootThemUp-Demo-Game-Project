// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuWidget.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/STULevelItemWidget.h"
#include "Menu/STUMenuPlayWidget.h"
#include "Menu/STUMenuSettingsWidget.h"
#include "UI/STUButtonWidget.h"

bool USTUMenuWidget::Initialize()
{
    const bool bResult = Super::Initialize();
    return bResult;
}

void USTUMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartGameButton != nullptr && StartGameButton->Get() != nullptr)
    {
        StartGameButton->Get()->OnClicked.AddDynamic(this, &USTUMenuWidget::StartGame);
    }

    if (ExitGameButton != nullptr && ExitGameButton->Get() != nullptr)
    {
        ExitGameButton->Get()->OnClicked.AddDynamic(this, &USTUMenuWidget::ExitGame);
    }

    if (SettingsButton != nullptr && SettingsButton->Get() != nullptr)
    {
        SettingsButton->Get()->OnClicked.AddDynamic(this, &USTUMenuWidget::ShowSettings);
    }

    GetWorld()->GetTimerManager().SetTimerForNextTick(
        [&]
        {
            StartGameButton->SetFocus(true);
        });
}

void USTUMenuWidget::StartGame()
{
    USTUMenuPlayWidget* MenuPlayWidget = CreateWidget<USTUMenuPlayWidget>(GetWorld(), PlayWidgetClass);
    if (MenuPlayWidget != nullptr)
    {
        MenuPlayWidget->AddToViewport();
        RemoveFromParent();
    }
}

void USTUMenuWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::ShowSettings()
{
    USTUMenuSettingsWidget* MenuSettingsWidget = CreateWidget<USTUMenuSettingsWidget>(GetWorld(), SettingsWidgetClass);
    if (MenuSettingsWidget != nullptr)
    {
        MenuSettingsWidget->AddToViewport();
        RemoveFromParent();
    }
}
