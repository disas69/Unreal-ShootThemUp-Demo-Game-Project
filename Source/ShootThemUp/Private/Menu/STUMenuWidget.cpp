// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuWidget.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/STULevelItemWidget.h"
#include "Menu/STUMenuPlayWidget.h"
#include "Menu/STUMenuSettingsWidget.h"

bool USTUMenuWidget::Initialize()
{
    const bool bResult = Super::Initialize();

    if (StartGameButton != nullptr)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::StartGame);
    }

    if (ExitGameButton != nullptr)
    {
        ExitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::ExitGame);
    }

    if (SettingsButton != nullptr)
    {
        SettingsButton->OnClicked.AddDynamic(this, &USTUMenuWidget::ShowSettings);
    }

    return bResult;
}

void USTUMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GetWorld()->GetTimerManager().SetTimerForNextTick(
        [&]
        {
            StartGameButton->SetKeyboardFocus();
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
