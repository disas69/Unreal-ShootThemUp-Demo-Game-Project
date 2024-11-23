// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuSettingsWidget.generated.h"

class USTUButtonWidget;
class USlider;
class UComboBoxString;

UCLASS()
class SHOOTTHEMUP_API USTUMenuSettingsWidget : public USTUBaseWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTUBaseWidget> MenuWidgetClass;
    
    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ResolutionSettings;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* QualitySettings;

    UPROPERTY(meta = (BindWidget))
    USlider* MusicVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    USlider* SFXVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    USTUButtonWidget* BackButton = nullptr;

    UFUNCTION()
    virtual bool Initialize() override;

    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void ShowMainMenu();

    UFUNCTION()
    void OnResolutionSelected(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnQualitySelected(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnMusicVolumeChanged(float Value);

    UFUNCTION()
    void OnSFXVolumeChanged(float Value);
};
