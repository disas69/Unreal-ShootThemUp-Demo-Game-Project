// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "GameSettingsSubsystem.h"
#include "GameFramework/GameUserSettings.h"

void UGameSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
    if (Settings)
    {
        // Set the overall scalability level to High
        Settings->SetOverallScalabilityLevel(2);
        Settings->SetFrameRateLimit(60.0f);
        Settings->ApplySettings(false);
    }
}

void UGameSettingsSubsystem::Deinitialize()
{
    Super::Deinitialize();
}