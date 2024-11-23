// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuWidget.generated.h"

class USTUButtonWidget;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION()
    virtual bool Initialize() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTUBaseWidget> PlayWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTUBaseWidget> SettingsWidgetClass;

    UPROPERTY(meta = (BindWidget))
    USTUButtonWidget* StartGameButton = nullptr;

    UPROPERTY(meta = (BindWidget))
    USTUButtonWidget* ExitGameButton = nullptr;

    UPROPERTY(meta = (BindWidget))
    USTUButtonWidget* SettingsButton = nullptr;
    
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void StartGame();

    UFUNCTION()
    void ExitGame();

    UFUNCTION()
    void ShowSettings();
};
