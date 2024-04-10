// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUGameModeBase.h"
#include "AIController.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "Player/STUPlayerState.h"
#include "UI/STUGameHUD.h"

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
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
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
            // Game over
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
    if (Controller != nullptr && Controller->GetPawn() != nullptr)
    {
        Controller->GetPawn()->Reset();
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

void ASTUGameModeBase::SetPlayerColor(AController* Controller)
{
    if (Controller == nullptr)
    {
        return;
    }

    ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
    if (Character != nullptr)
    {
        const ASTUPlayerState* PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
        if (PlayerState != nullptr)
        {
            Character->SetPlayerColor(PlayerState->GetTeamColor());
        }
    }
}