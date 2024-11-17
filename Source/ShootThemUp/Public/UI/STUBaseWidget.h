// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUBaseWidget.generated.h"

class USoundCue;

UCLASS()
class SHOOTTHEMUP_API USTUBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void Show(bool bAnimate = true);

protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* ShowSound;
};
