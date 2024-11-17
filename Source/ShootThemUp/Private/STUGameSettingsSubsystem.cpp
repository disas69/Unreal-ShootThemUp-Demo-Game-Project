// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUGameSettingsSubsystem.h"
#include "STUGameInstance.h"
#include "STUSaveGame.h"
#include "GameFramework/GameUserSettings.h"

USTUGameSettingsSubsystem* USTUGameSettingsSubsystem::GetGameSettingsSubsystem(const UObject* ContextObject)
{
    if (!ContextObject || !ContextObject->GetWorld() || !ContextObject->GetWorld()->GetGameInstance())
    {
        return nullptr;
    }
    
    return ContextObject->GetWorld()->GetGameInstance()->GetSubsystem<USTUGameSettingsSubsystem>();
}

void USTUGameSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    USTUGameInstance* GameInstance = Cast<USTUGameInstance>(GetGameInstance());
    if (GameInstance != nullptr)
    {
        USTUSaveGame* GameData = GameInstance->GetGameData();
        if (GameData != nullptr)
        {
            UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
            if (Settings)
            {
                FVector2D ScreenResolution = ScreenResolutions[GameData->GameSettingsSave.ScreenResolution];
                Settings->SetScreenResolution(FIntPoint(ScreenResolution.X, ScreenResolution.Y));
                Settings->ApplyResolutionSettings(false);
        
                int32 QualityLevel = QualityPresets[GameData->GameSettingsSave.QualityPreset];
                Settings->SetOverallScalabilityLevel(QualityLevel);
                Settings->SetFrameRateLimit(60.0f);
                Settings->ApplySettings(false);
            }
        }
    }
}

void USTUGameSettingsSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

FString USTUGameSettingsSubsystem::GetCurrentScreenResolution() const
{
    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
    if (UserSettings != nullptr)
    {
        const FIntPoint CurrentScreenResolution = UserSettings->GetScreenResolution();
        return FString::Printf(TEXT("%dx%d"), CurrentScreenResolution.X, CurrentScreenResolution.Y);
    }

    return "None";
}

FString USTUGameSettingsSubsystem::GetCurrentQualityPreset() const
{
    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
    if (UserSettings != nullptr)
    {
        int32 QualityLevel = UserSettings->GetOverallScalabilityLevel();
        TArray<FString> QualityNames;
        QualityPresets.GetKeys(QualityNames);

        return QualityNames.IsValidIndex(QualityLevel) ? QualityNames[QualityLevel] : "None";
    }

    return "None";
}

void USTUGameSettingsSubsystem::SetScreenResolution(const FString& Resolution) const
{
    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
    if (UserSettings != nullptr)
    {
        const FVector2D& ResolutionValue = ScreenResolutions.FindRef(Resolution);
        UserSettings->SetScreenResolution(FIntPoint(ResolutionValue.X, ResolutionValue.Y));
        UserSettings->ApplyResolutionSettings(false);
        UserSettings->ApplySettings(false);
    }

    // Save resolution to the save game
    USTUGameInstance* GameInstance = Cast<USTUGameInstance>(GetGameInstance());
    if (GameInstance != nullptr)
    {
        USTUSaveGame* GameData = GameInstance->GetGameData();
        if (GameData != nullptr)
        {
            GameData->GameSettingsSave.ScreenResolution = Resolution;
            GameInstance->SaveGameData();
        }
    }
}

void USTUGameSettingsSubsystem::SetQualityPreset(const FString& Quality) const
{
    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
    if (UserSettings != nullptr)
    {
        const int32 QualityLevel = QualityPresets.FindRef(Quality);
        UserSettings->SetOverallScalabilityLevel(QualityLevel);
        UserSettings->ApplySettings(false);
    }

    // Save quality preset to the save game
    USTUGameInstance* GameInstance = Cast<USTUGameInstance>(GetGameInstance());
    if (GameInstance != nullptr)
    {
        USTUSaveGame* GameData = GameInstance->GetGameData();
        if (GameData != nullptr)
        {
            GameData->GameSettingsSave.QualityPreset = Quality;
            GameInstance->SaveGameData();
        }
    }
}