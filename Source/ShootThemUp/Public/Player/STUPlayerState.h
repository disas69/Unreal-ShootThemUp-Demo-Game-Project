// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    void SetTeam(const int32 NewTeamID, const FLinearColor NewTeamColor);

    int32 GetTeamID() const { return TeamID; }
    FLinearColor GetTeamColor() const { return TeamColor; }

    void AddKill() { ++KillsNum; }
    void AddDeath() { ++DeathsNum; }
    int32 GetKillsNum() const { return KillsNum; }
    int32 GetDeathsNum() const { return DeathsNum; }

    void PrintStateLog() const;

private:
    int32 TeamID = 0;
    FLinearColor TeamColor = FLinearColor::Red;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;
};
