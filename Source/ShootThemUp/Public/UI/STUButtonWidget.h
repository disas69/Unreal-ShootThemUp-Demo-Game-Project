// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUButtonWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUButtonWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    UButton* Button = nullptr;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextBlock = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FText Text;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FLinearColor DefaultColor = FLinearColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FLinearColor FocusedColor = FLinearColor::Red;

    void SetFocus(bool bFocus);
    UButton* Get() const { return Button; }

protected:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
