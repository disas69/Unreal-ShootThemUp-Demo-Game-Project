// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FVector2D CrossHairOffset = FVector2D(0.0f, 0.0f);
    
    virtual void DrawHUD() override;

    FVector2D GetCrossHairPosition() const;

private:
    void DrawCrossHair();
};
