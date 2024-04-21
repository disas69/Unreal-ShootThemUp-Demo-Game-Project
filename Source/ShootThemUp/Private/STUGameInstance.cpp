// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/STUSoundStatics.h"
#include "Sound/SoundClass.h"

void USTUGameInstance::OpenMenuLevel() const
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, MenuLevel);
}

void USTUGameInstance::OpenGameLevel(int32 LevelIndex) const
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, GetLevelData(LevelIndex).Level);
}

void USTUGameInstance::ToggleVolume() const
{
    USTUSoundStatics::ToggleSoundClassVolume(MasterSoundClass);
}

void USTUGameInstance::SetMusicVolume(float Volume) const
{
    USTUSoundStatics::SetSoundClassVolume(MusicSoundClass, Volume);
}

void USTUGameInstance::SetSFXVolume(float Volume) const
{
    USTUSoundStatics::SetSoundClassVolume(SFXSoundClass, Volume);
}

float USTUGameInstance::GetMusicVolume() const
{
    if (MusicSoundClass == nullptr)
    {
        return 0.0f;
    }

    return MusicSoundClass->Properties.Volume;
}

float USTUGameInstance::GetSFXVolume() const
{
    if (SFXSoundClass == nullptr)
    {
        return 0.0f;
    }

    return SFXSoundClass->Properties.Volume;
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