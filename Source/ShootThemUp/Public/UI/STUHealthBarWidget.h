// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTTHEMUP_API USTUHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetHealthPercent(float Percent);
    void SetDistanceVisibility(float Distance);

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float ValueVisibilityThreshold = 0.8f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float DistanceVisibilityThreshold = 1000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float CriticalHealthThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor NormalColor = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor CriticalColor = FLinearColor::Red;
};
