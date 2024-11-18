// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuSettingsWidget.h"
#include "STUGameInstance.h"
#include "STUGameSettingsSubsystem.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Menu/STUMenuWidget.h"

bool USTUMenuSettingsWidget::Initialize()
{
    const bool bResult = Super::Initialize();

    USTUGameSettingsSubsystem* GameSettingsSubsystem = USTUGameSettingsSubsystem::GetGameSettingsSubsystem(this);
    if (GameSettingsSubsystem != nullptr)
    {
        if (ResolutionSettings != nullptr)
        {
            for (const auto& Resolution : GameSettingsSubsystem->GetScreenResolutions())
            {
                ResolutionSettings->AddOption(Resolution.Key);
            }

            ResolutionSettings->SetSelectedOption(GameSettingsSubsystem->GetCurrentScreenResolution());
            ResolutionSettings->OnSelectionChanged.AddDynamic(this, &USTUMenuSettingsWidget::OnResolutionSelected);
        }

        if (QualitySettings != nullptr)
        {
            for (const auto& Quality : GameSettingsSubsystem->GetQualityPresets())
            {
                QualitySettings->AddOption(Quality.Key);
            }

            QualitySettings->SetSelectedOption(GameSettingsSubsystem->GetCurrentQualityPreset());
            QualitySettings->OnSelectionChanged.AddDynamic(this, &USTUMenuSettingsWidget::OnQualitySelected);
        }
    }

    if (MusicVolumeSlider != nullptr)
    {
        MusicVolumeSlider->OnValueChanged.AddDynamic(this, &USTUMenuSettingsWidget::OnMusicVolumeChanged);
    }

    if (SFXVolumeSlider != nullptr)
    {
        SFXVolumeSlider->OnValueChanged.AddDynamic(this, &USTUMenuSettingsWidget::OnSFXVolumeChanged);
    }

    const USTUGameInstance* GameInstance = GetGameInstance<USTUGameInstance>();
    if (GameInstance != nullptr)
    {
        if (MusicVolumeSlider != nullptr)
        {
            MusicVolumeSlider->SetValue(GameInstance->GetMusicVolume());
        }

        if (SFXVolumeSlider != nullptr)
        {
            SFXVolumeSlider->SetValue(GameInstance->GetSFXVolume());
        }
    }

    if (BackButton != nullptr)
    {
        BackButton->OnClicked.AddDynamic(this, &USTUMenuSettingsWidget::ShowMainMenu);
    }

    return bResult;
}

void USTUMenuSettingsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GetWorld()->GetTimerManager().SetTimerForNextTick(
    [&]
    {
        BackButton->SetKeyboardFocus();
    });
}

void USTUMenuSettingsWidget::ShowMainMenu()
{
    USTUMenuWidget* MenuWidget = CreateWidget<USTUMenuWidget>(GetWorld(), MenuWidgetClass);
    if (MenuWidget != nullptr)
    {
        MenuWidget->AddToViewport();
        MenuWidget->Show(false);
        RemoveFromParent();
    }
}

void USTUMenuSettingsWidget::OnResolutionSelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    USTUGameSettingsSubsystem* GameSettingsSubsystem = USTUGameSettingsSubsystem::GetGameSettingsSubsystem(this);
    if (GameSettingsSubsystem != nullptr)
    {
        GameSettingsSubsystem->SetScreenResolution(SelectedItem);
    }
}

void USTUMenuSettingsWidget::OnQualitySelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    USTUGameSettingsSubsystem* GameSettingsSubsystem = USTUGameSettingsSubsystem::GetGameSettingsSubsystem(this);
    if (GameSettingsSubsystem != nullptr)
    {
        GameSettingsSubsystem->SetQualityPreset(SelectedItem);
    }
}

void USTUMenuSettingsWidget::OnMusicVolumeChanged(float Value)
{
    const USTUGameInstance* GameInstance = GetGameInstance<USTUGameInstance>();
    if (GameInstance != nullptr)
    {
        GameInstance->SetMusicVolume(Value);
    }
}

void USTUMenuSettingsWidget::OnSFXVolumeChanged(float Value)
{
    const USTUGameInstance* GameInstance = GetGameInstance<USTUGameInstance>();
    if (GameInstance != nullptr)
    {
        GameInstance->SetSFXVolume(Value);
    }
}