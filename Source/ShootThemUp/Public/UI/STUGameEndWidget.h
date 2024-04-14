// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "STUGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "STUGameEndWidget.generated.h"

class UButton;
class USTUPlayerStatsWidget;
class UVerticalBox;

UCLASS()
class SHOOTTHEMUP_API USTUGameEndWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTUPlayerStatsWidget> PlayerStatsWidgetClass;
    
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatsBox;

    UPROPERTY(meta = (BindWidget))
    UButton* RestartLevelButton;

private:
    void OnGameStateChange(EGameState NewState);
    void DisplayPlayersStats();

    UFUNCTION()
    void RestartLevel();
};
