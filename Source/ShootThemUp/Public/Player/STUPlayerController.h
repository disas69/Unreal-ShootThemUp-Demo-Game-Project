// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class ASTUBaseCharacter;
class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASTUPlayerController();

    APawn* GetCharacterPawn();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTURespawnComponent* STURespawnComponent;

    virtual void OnPossess(APawn* InPawn) override;

private:
    UPROPERTY()
    ASTUBaseCharacter* CharacterPawn = nullptr;
};
