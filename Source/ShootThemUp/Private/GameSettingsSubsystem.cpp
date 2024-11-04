// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "GameSettingsSubsystem.h"
#include "GameFramework/GameUserSettings.h"

UGameSettingsSubsystem* UGameSettingsSubsystem::GetGameSettingsSubsystem(const UObject* ContextObject)
{
    return ContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UGameSettingsSubsystem>();
}

void UGameSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UGameUserSettings* Settings = UGameUserSettings::GetGameUserSettings();
    if (Settings)
    {
        // Set the screen resolution to the highest available
        FVector2D HighestScreenResolution = ScreenResolutions["1920x1080"];
        Settings->SetScreenResolution(FIntPoint(HighestScreenResolution.X, HighestScreenResolution.Y));
        Settings->ApplyResolutionSettings(false);
        
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

FString UGameSettingsSubsystem::GetCurrentScreenResolution() const
{
    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
    if (UserSettings != nullptr)
    {
        const FIntPoint CurrentScreenResolution = UserSettings->GetScreenResolution();
        return FString::Printf(TEXT("%dx%d"), CurrentScreenResolution.X, CurrentScreenResolution.Y);
    }

    return "None";
}

FString UGameSettingsSubsystem::GetCurrentQualityPreset() const
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

void UGameSettingsSubsystem::SetScreenResolution(const FString& Resolution) const
{
    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
    if (UserSettings != nullptr)
    {
        const FVector2D& ResolutionValue = ScreenResolutions.FindRef(Resolution);
        UserSettings->SetScreenResolution(FIntPoint(ResolutionValue.X, ResolutionValue.Y));
        UserSettings->ApplyResolutionSettings(false);
    }
}

void UGameSettingsSubsystem::SetQualityPreset(const FString& Quality) const
{
    UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
    if (UserSettings != nullptr)
    {
        const int32 QualityLevel = QualityPresets.FindRef(Quality);
        UserSettings->SetOverallScalabilityLevel(QualityLevel);
        UserSettings->ApplySettings(false);
    }
}