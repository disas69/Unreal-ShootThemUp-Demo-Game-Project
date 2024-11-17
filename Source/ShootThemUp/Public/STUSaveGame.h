// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "STUSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FGameSettingsSave
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString ScreenResolution = "1920x1080";

    UPROPERTY(BlueprintReadWrite)
    FString QualityPreset = "High";
};

UCLASS()
class SHOOTTHEMUP_API USTUSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    FGameSettingsSave GameSettingsSave;
};
