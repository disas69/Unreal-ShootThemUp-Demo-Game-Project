// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUBaseWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void Show();

protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;
};
