// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuPlayWidget.generated.h"

class UButton;
class USTULevelItemWidget;
class UHorizontalBox;

UCLASS()
class SHOOTTHEMUP_API USTUMenuPlayWidget : public USTUBaseWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTUBaseWidget> MenuWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTULevelItemWidget> LevelItemWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* LoadingAnimation;

    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* BackButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;

    UFUNCTION()
    virtual bool Initialize() override;

    virtual void NativeConstruct() override;

protected:
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    int32 SelectedIndex = -1;

    UPROPERTY()
    TArray<USTULevelItemWidget*> LevelItemWidgets;

    void CreateLevelItems();
    void LoadSelectedLevel();

    UFUNCTION()
    void OnLevelItemSelected(int32 Index);

    UFUNCTION()
    void OnLevelItemFocused(int32 Index);

    UFUNCTION()
    void StartGame();

    UFUNCTION()
    void OpenMenu();
};
