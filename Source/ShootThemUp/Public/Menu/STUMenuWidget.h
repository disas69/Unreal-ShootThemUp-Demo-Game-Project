// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUMenuWidget.generated.h"

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
    TSubclassOf<USTUBaseWidget> PlayWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTUBaseWidget> SettingsWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* SettingsButton;
    
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void StartGame();

    UFUNCTION()
    void ExitGame();

    UFUNCTION()
    void ShowSettings();
};
