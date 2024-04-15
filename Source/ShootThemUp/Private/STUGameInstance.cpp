// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USTUGameInstance::OpenMenuLevel() const
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, MenuLevel);
}

void USTUGameInstance::OpenGameLevel(int32 LevelIndex) const
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, StartLevel);
}