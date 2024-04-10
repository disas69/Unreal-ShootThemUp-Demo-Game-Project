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
    int32 GetTeamID() const { return TeamID; }
    FLinearColor GetTeamColor() const { return TeamColor; }
    void SetTeam(const int32 NewTeamID, const FLinearColor NewTeamColor);

private:
    int32 TeamID = 0;
    FLinearColor TeamColor = FLinearColor::Red;
};
