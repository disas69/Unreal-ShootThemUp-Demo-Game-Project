// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "STUPlayerStart.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
    int32 GetTeamID() const { return TeamID; }
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
    int32 TeamID = -1;
};
