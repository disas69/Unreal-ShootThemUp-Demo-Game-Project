// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUGameModeBase.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
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

bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const bool bResult = Super::SetPause(PC, CanUnpauseDelegate);
    if (bResult)
    {
        StopAllPlayers();
        SetGameState(EGameState::Pause);
    }

    return bResult;
}

bool ASTUGameModeBase::ClearPause()
{
    const bool bResult = Super::ClearPause();
    if (bResult)
    {
        SetGameState(EGameState::Gameplay);
    }
    
    return bResult;
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

void ASTUGameModeBase::OnPlayerDamageApplied(const AActor* DamagedActor, float Damage, const AController* InstigatedBy) const
{
    if (InstigatedBy == nullptr)
    {
        return;
    }

    if (InstigatedBy->IsPlayerController())
    {
        PlayerDamagedActor.Broadcast(DamagedActor, Damage);
    }
}

void ASTUGameModeBase::InitPlayer(AController* Controller)
{
    if (Controller == nullptr)
    {
        return;
    }
    
    RestartPlayer(Controller);

    USTUHealthComponent* HealthComponent = FSTUUtils::GetActorComponent<USTUHealthComponent>(Controller->GetPawn());
    if (HealthComponent)
    {
        HealthComponent->OnDamageApplied.AddUObject(this, &ASTUGameModeBase::OnPlayerDamageApplied);
    }
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
        InitPlayer(AIController);
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

    InitPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTUGameModeBase::StopAllPlayers() const
{
    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const AController* Controller = It->Get();
        ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
        if (Character != nullptr)
        {
            Character->StopPlayer();
        }
    }
}

void ASTUGameModeBase::CreateTeams()
{
    int32 TeamID = 0;
    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        AController* Controller = It->Get();
        if (Controller == nullptr)
        {
            continue;
        }
        
        ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (PlayerState != nullptr)
        {
            if (Controller->IsPlayerController())
            {
                PlayerState->SetPlayerName("Player");
            }
            else
            {
                PlayerState->SetPlayerName("Bot");
            }
            PlayerState->SetTeamData(TeamID, GetTeamData(TeamID));
            SetPlayerColor(It->Get());
            TeamID = (TeamID + 1) % GameData.Teams.Num();
        }
    }
}

FTeamData ASTUGameModeBase::GetTeamData(int32 TeamID) const
{
    FTeamData Result;
    
    if (TeamID >= 0 && TeamID < GameData.Teams.Num())
    {
        Result = GameData.Teams[TeamID];
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
            Character->SetPlayerColor(PlayerState->GetTeamData().Color);
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

        USTURespawnComponent* RespawnComponent = FSTUUtils::GetActorComponent<USTURespawnComponent>(Pawn);
        if (RespawnComponent)
        {
            RespawnComponent->CancelRespawn();
        }
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