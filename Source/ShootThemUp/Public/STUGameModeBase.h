// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameModeBase.generated.h"

class AAIController;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGameState);

UENUM(BlueprintType)
enum class EGameState : uint8
{
    Waiting,
    Gameplay,
    Pause,
    Finished
};

USTRUCT(BlueprintType)
struct FTeamData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    FString Name = "Team";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    FLinearColor Color = FLinearColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    UTexture2D* Icon = nullptr;
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    int32 PlayersNum = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    int32 RoundsNum = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    float RoundTime = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    float RespawnTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams")
    FLinearColor DefaultTeamColor = FLinearColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams")
    TArray<FTeamData> Teams;
};

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASTUGameModeBase();

    FOnGameStateChanged GameStateChanged;

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;

    void OnPlayerKilled(AController* PlayerKilled, const AController* PlayerKiller);

    int32 GetCurrentRoundNum() const { return CurrentRound; }
    int32 GetTotalRoundsNum() const { return GameData.RoundsNum; }
    float GetRoundCountdown() const { return RoundCountDown; }

    void ScheduleRespawn(AController* Controller) const;
    void Respawn(AController* Controller);

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
    EGameState GameState = EGameState::Waiting;

    void SetGameState(EGameState NewState);
    void SpawnPlayers();
    void StartRound();
    void UpdateRoundTimer();
    void ResetAllPlayers();
    void ResetPlayer(AController* Controller);
    void StopAllPlayers() const;

    void CreateTeams();
    FTeamData GetTeamData(int32 TeamID) const;
    void SetPlayerColor(const AController* Controller);

    void GameOver();
    void LogPlayerStates() const;
};
