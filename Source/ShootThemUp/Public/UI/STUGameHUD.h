// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "STUGameModeBase.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

class USTUPlayerHUDWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FVector2D CrossHairOffset = FVector2D(0.0f, 0.0f);

    FVector2D GetCrossHairPosition() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameEndWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;
    
    UPROPERTY()
    TMap<EGameState, UUserWidget*> GameWidgets;

    void CreateGameWidgets();
    void DisplayGameWidget(EGameState NewState);
    void OnGameStateChanged(EGameState NewState);
    
    void DrawDebugCrossHair();
};
