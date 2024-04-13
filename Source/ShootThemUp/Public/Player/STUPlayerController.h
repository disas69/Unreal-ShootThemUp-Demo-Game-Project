// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "STUGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "STUPlayerController.generated.h"

class UInputDataConfig;
class ASTUBaseCharacter;
class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASTUPlayerController();
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputDataConfig* InputDataConfig = nullptr;

    APawn* GetCharacterPawn();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTURespawnComponent* STURespawnComponent;
    
    virtual void BeginPlay() override;
    
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;

private:
    UPROPERTY()
    ASTUBaseCharacter* CharacterPawn = nullptr;

    void OnGameStateChanged(EGameState GameState);
    void OnGamePaused();
};
