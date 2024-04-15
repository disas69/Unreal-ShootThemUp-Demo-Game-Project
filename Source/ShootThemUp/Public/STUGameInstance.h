// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    void OpenMenuLevel() const;
    void OpenGameLevel(int32 LevelIndex) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSoftObjectPtr<UWorld> MenuLevel;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSoftObjectPtr<UWorld> StartLevel;
};
