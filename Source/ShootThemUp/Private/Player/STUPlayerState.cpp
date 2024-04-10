// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Player/STUPlayerState.h"

void ASTUPlayerState::SetTeam(const int32 NewTeamID, const FLinearColor NewTeamColor)
{
    TeamID = NewTeamID;
    TeamColor = NewTeamColor;
}