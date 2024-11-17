// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

class USTUSaveGame;
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
    virtual void Init() override;
    
    void OpenMenuLevel() const;
    void OpenGameLevel(int32 LevelIndex) const;

    FORCEINLINE const TArray<FLevelData>& GetGameLevels() const { return GameLevels; }
    FORCEINLINE USTUSaveGame* GetGameData() const { return GameData; }

    void ToggleVolume() const;
    void SetMusicVolume(float Volume) const;
    void SetSFXVolume(float Volume) const;
    float GetMusicVolume() const;
    float GetSFXVolume() const;

    UFUNCTION(BlueprintCallable, Category = "Game")
    void LoadGameData();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void SaveGameData();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FString SaveGameSlotName = "SaveGame";

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    USTUSaveGame* GameData = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSoftObjectPtr<UWorld> MenuLevel;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TArray<FLevelData> GameLevels;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    USoundClass* MasterSoundClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    USoundClass* MusicSoundClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    USoundClass* SFXSoundClass;

private:
    FLevelData GetLevelData(int32 Index) const;
};
