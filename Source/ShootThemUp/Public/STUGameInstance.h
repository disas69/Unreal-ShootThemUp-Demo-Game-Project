// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

USTRUCT()
struct FLevelData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FString Name;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    UTexture2D* Preview;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSoftObjectPtr<UWorld> Level;
};

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    void OpenMenuLevel() const;
    void OpenGameLevel(int32 LevelIndex) const;

    const TArray<FLevelData>& GetGameLevels() const { return GameLevels; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSoftObjectPtr<UWorld> MenuLevel;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TArray<FLevelData> GameLevels;

private:
    FLevelData GetLevelData(int32 Index) const;
};
