// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUMenuHUD.generated.h"

class USTUBaseWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUMenuHUD : public AHUD
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<USTUBaseWidget> MenuWidgetClass;

    virtual void BeginPlay() override;
};
