// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USTUGameInstance::OpenMenuLevel() const
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, MenuLevel);
}

void USTUGameInstance::OpenGameLevel(int32 LevelIndex) const
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, GetLevelData(LevelIndex).Level);
}

FLevelData USTUGameInstance::GetLevelData(int32 Index) const
{
    if (Index < 0 || Index >= GameLevels.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Level index is out of range!"));
        return FLevelData();
    }

    return GameLevels[Index];
}