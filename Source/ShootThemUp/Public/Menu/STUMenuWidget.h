// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuWidget.generated.h"

class UComboBoxString;
class USlider;
class USoundCue;
class USTULevelItemWidget;
class UHorizontalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION()
    virtual bool Initialize() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTULevelItemWidget> LevelItemWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* SettingsButton;

    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ResolutionSettings;
    
    UPROPERTY(meta = (BindWidget))
    UComboBoxString* QualitySettings;

    UPROPERTY(meta = (BindWidget))
    USlider* MusicVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    USlider* SFXVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    UButton* BackButton;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* LoadingAnimation;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowSettingsAnimation;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowMenuAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;

    virtual void NativeConstruct() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    int32 SelectedIndex = -1;

    TMap<FString, FVector2D> ScreenResolutions = {{"1920x1080", FVector2D(1920, 1080)}, {"1280x720", FVector2D(1280, 720)}, {"800x600", FVector2D(800, 600)}};
    TMap<FString, int32> QualityPresets = {{"Low", 0}, {"Medium", 1}, {"High", 2}, {"Epic", 3}};

    UPROPERTY()
    TArray<USTULevelItemWidget*> LevelItemWidgets;

    UFUNCTION()
    void StartGame();

    UFUNCTION()
    void ExitGame();

    UFUNCTION()
    void ShowSettings();

    UFUNCTION()
    void OnResolutionSelected(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnQualitySelected(FString SelectedItem, ESelectInfo::Type SelectionType);

    UFUNCTION()
    void OnMusicVolumeChanged(float Value);

    UFUNCTION()
    void OnSFXVolumeChanged(float Value);

    UFUNCTION()
    void ShowMainMenu();

    void CreateLevelItems();
    void OnLevelItemSelected(int32 Index);
    void OnLevelItemFocused(int32 Index);

    void LoadSelectedLevel();
};
