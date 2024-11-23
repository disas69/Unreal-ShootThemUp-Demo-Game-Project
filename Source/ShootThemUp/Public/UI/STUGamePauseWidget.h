// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "STUGamePauseWidget.generated.h"

class USTUButtonWidget;

UCLASS()
class SHOOTTHEMUP_API USTUGamePauseWidget : public USTUBaseWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;
    virtual void SetVisibility(ESlateVisibility InVisibility) override;

protected:
    UPROPERTY(meta = (BindWidget))
    USTUButtonWidget* ContinueButton = nullptr;

    UPROPERTY(meta = (BindWidget))
    USTUButtonWidget* ExitButton = nullptr;

    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void ContinueGame();

    UFUNCTION()
    void ExitGame();
};
