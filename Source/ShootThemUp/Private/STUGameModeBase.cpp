// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUGameModeBase.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "Player/STUPlayerState.h"
#include "UI/STUGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
    PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnPlayers();
    CreateTeams();

    CurrentRound = 1;
    StartRound();
    
    SetGameState(EGameState::Gameplay);
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::OnPlayerKilled(AController* PlayerKilled, const AController* PlayerKiller)
{
    ASTUPlayerState* KilledPlayerState = PlayerKilled != nullptr ? Cast<ASTUPlayerState>(PlayerKilled->PlayerState) : nullptr;
    if (KilledPlayerState != nullptr)
    {
        KilledPlayerState->AddDeath();
    }

    ASTUPlayerState* KillerPlayerState = PlayerKiller != nullptr ? Cast<ASTUPlayerState>(PlayerKiller->PlayerState) : nullptr;
    if (KillerPlayerState != nullptr)
    {
        KillerPlayerState->AddKill();
    }

    ScheduleRespawn(PlayerKilled);
}

void ASTUGameModeBase::ScheduleRespawn(AController* Controller) const
{
    USTURespawnComponent* RespawnComponent = FSTUUtils::GetActorComponent<USTURespawnComponent>(Controller);
    if (RespawnComponent)
    {
        RespawnComponent->Respawn(GameData.RespawnTime);
    }
}

void ASTUGameModeBase::Respawn(AController* Controller)
{
    ResetPlayer(Controller);
}

void ASTUGameModeBase::SetGameState(EGameState NewState)
{
    if (GameState == NewState)
    {
        return;
    }

    GameState = NewState;
    GameStateChanged.Broadcast(GameState);
}

void ASTUGameModeBase::SpawnPlayers()
{
    const int32 PlayersNum = FMath::Max(0, GameData.PlayersNum - 1);

    for (int32 i = 0; i < PlayersNum; i++)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        AAIController* AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(AIController);
    }
}

void ASTUGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::UpdateRoundTimer, 1.0f, true);
    LogPlayerStates();
}

void ASTUGameModeBase::UpdateRoundTimer()
{
    RoundCountDown -= GetWorldTimerManager().GetTimerRate(GameRoundTimerHandle);

    if (RoundCountDown <= 0.0f)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            CurrentRound++;
            StartRound();
            ResetAllPlayers();
        }
        else
        {
            GameOver();
        }
    }
}

void ASTUGameModeBase::ResetAllPlayers()
{
    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetPlayer(It->Get());
    }
}

void ASTUGameModeBase::ResetPlayer(AController* Controller)
{
    if (Controller != nullptr)
    {
        USTURespawnComponent* RespawnComponent = FSTUUtils::GetActorComponent<USTURespawnComponent>(Controller);
        if (RespawnComponent)
        {
            RespawnComponent->CancelRespawn();
        }

        // Player's Pawn is already detached from the controller due to the spectator mode
        ASTUPlayerController* PlayerController = Cast<ASTUPlayerController>(Controller);
        if (PlayerController != nullptr)
        {
            APawn* PlayerPawn = PlayerController->GetCharacterPawn();
            if (PlayerPawn != nullptr)
            {
                PlayerPawn->Reset();
            }
        }
        else
        {
            APawn* AIPawn = Controller->GetPawn();
            if (AIPawn != nullptr)
            {
                AIPawn->Reset();
            }
        }
    }

    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTUGameModeBase::CreateTeams()
{
    int32 TeamID = 0;
    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(It->Get()->PlayerState);
        if (PlayerState != nullptr)
        {
            PlayerState->SetTeam(TeamID, GetTeamColor(TeamID));
            SetPlayerColor(It->Get());
            TeamID = (TeamID + 1) % GameData.TeamsColors.Num();
        }
    }
}

FLinearColor ASTUGameModeBase::GetTeamColor(int32 TeamID) const
{
    FLinearColor Result = GameData.DefaultTeamColor;
    if (TeamID >= 0 && TeamID < GameData.TeamsColors.Num())
    {
        Result = GameData.TeamsColors[TeamID];
    }

    return Result;
}

void ASTUGameModeBase::SetPlayerColor(const AController* Controller)
{
    if (Controller == nullptr)
    {
        return;
    }

    const ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
    if (Character != nullptr)
    {
        const ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (PlayerState != nullptr)
        {
            Character->SetPlayerColor(PlayerState->GetTeamColor());
        }
    }
}

void ASTUGameModeBase::GameOver()
{
    SetGameState(EGameState::Finished);
    
    for (APawn* Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn == nullptr)
        {
            continue;
        }

        Pawn->TurnOff();
        Pawn->DisableInput(nullptr);
    }
    
    LogPlayerStates();
}

void ASTUGameModeBase::LogPlayerStates() const
{
    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(It->Get()->PlayerState);
        if (PlayerState != nullptr)
        {
            PlayerState->PrintStateLog();
        }
    }
}