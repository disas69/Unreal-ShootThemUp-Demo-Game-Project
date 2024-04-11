// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetTimerText() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetRoundsText() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetScoreText() const;

private:
    float GetRoundTime() const;
    int32 GetCurrentRoundNum() const;
    int32 GetTotalRoundsNum() const;
    int32 GetKillsNum() const;
    FString GetTimeFormattedText(float TimeSeconds) const;
};
