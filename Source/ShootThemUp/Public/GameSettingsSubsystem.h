// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameSettingsSubsystem.generated.h"

UCLASS()
class SHOOTTHEMUP_API UGameSettingsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UGameSettingsSubsystem* GetGameSettingsSubsystem(const UObject* ContextObject);
    
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    FORCEINLINE TMap<FString, FVector2D> GetScreenResolutions() const { return ScreenResolutions; }
    FORCEINLINE TMap<FString, int32> GetQualityPresets() const { return QualityPresets; }

    FString GetCurrentScreenResolution() const;
    FString GetCurrentQualityPreset() const;

    void SetScreenResolution(const FString& Resolution) const;
    void SetQualityPreset(const FString& Quality) const;

private:
    TMap<FString, FVector2D> ScreenResolutions = {{"1920x1080", FVector2D(1920, 1080)}, {"1280x720", FVector2D(1280, 720)}, {"800x600", FVector2D(800, 600)}};
    TMap<FString, int32> QualityPresets = {{"Low", 0}, {"Medium", 1}, {"High", 2}, {"Epic", 3}};
};
