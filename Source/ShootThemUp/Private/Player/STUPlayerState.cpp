// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All);

void ASTUPlayerState::SetTeamData(const int32 NewTeamID, const FTeamData& NewTeamData)
{
    TeamID = NewTeamID;
    TeamData = NewTeamData;
}

void ASTUPlayerState::PrintStateLog() const
{
    const FString LogMessage = FString::Printf(TEXT("PlayerState: %s, TeamID: %i, TeamColor: %s, Kills: %i, Deaths: %i"), *GetPlayerName(), TeamID, *GetTeamData().Color.ToString(), KillsNum, DeathsNum);
    UE_LOG(LogSTUPlayerState, Display, TEXT("%s"), *LogMessage);
}