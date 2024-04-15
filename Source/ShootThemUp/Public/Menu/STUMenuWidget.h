// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

class USTULevelItemWidget;
class UHorizontalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTULevelItemWidget> LevelItemWidgetClass;
    
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;
    
    UPROPERTY(meta=(BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta=(BindWidget))
    UButton* ExitGameButton;

private:
    int32 SelectedIndex = -1;
    
    UPROPERTY()
    TArray<USTULevelItemWidget*> LevelItemWidgets;
    
    UFUNCTION()
    void StartGame();

    UFUNCTION()
    void ExitGame();

    void CreateLevelItems();
    void OnLevelItemSelected(int32 Index);
};
