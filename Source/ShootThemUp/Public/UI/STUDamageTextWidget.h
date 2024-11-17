// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUDamageTextWidget.generated.h"

class UTextBlock;
UCLASS()
class SHOOTTHEMUP_API USTUDamageTextWidget : public USTUBaseWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* DamageText;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    float LifeTime = 1.0f;

    void SetDamageText(const FString& Text) const;

    virtual void Show(bool bAnimate = true) override;
};
