// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Sound/STUSoundStatics.h"
#include "Sound/SoundClass.h"

void USTUSoundStatics::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if (SoundClass == nullptr)
    {
        return;
    }
    
    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void USTUSoundStatics::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if (SoundClass == nullptr)
    {
        return;
    }
    
    if (SoundClass->Properties.Volume > 0.0f)
    {
        SoundClass->Properties.Volume = 0.0f;
    }
    else
    {
        SoundClass->Properties.Volume = 1.0f;
    }
}