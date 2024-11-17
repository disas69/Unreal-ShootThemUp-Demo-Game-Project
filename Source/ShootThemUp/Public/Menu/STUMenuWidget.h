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
    TSubclassOf<USTUBaseWidget> SettingsWidgetClass;
    
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

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* LoadingAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;

    virtual void NativeConstruct() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    int32 SelectedIndex = -1;

    UPROPERTY()
    TArray<USTULevelItemWidget*> LevelItemWidgets;

    UFUNCTION()
    void StartGame();

    UFUNCTION()
    void ExitGame();

    UFUNCTION()
    void ShowSettings();

    void CreateLevelItems();
    void OnLevelItemSelected(int32 Index);
    void OnLevelItemFocused(int32 Index);

    void LoadSelectedLevel();
};
