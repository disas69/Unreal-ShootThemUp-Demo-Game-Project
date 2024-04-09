// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.generated.h"

class AAIController;

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    int32 PlayersNum = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    int32 RoundsNum = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    float RoundTime = 60;
};

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
    int32 CurrentRound = 1;
    float RoundCountDown = 0.0f;
    FTimerHandle GameRoundTimerHandle;
    
    void SpawnPlayers();
    void StartRound();
    void UpdateRoundTimer();
    void ResetAllPlayers();
    void ResetPlayer(AController* Controller);
};
