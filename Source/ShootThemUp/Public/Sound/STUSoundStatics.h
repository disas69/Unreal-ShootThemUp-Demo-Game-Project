// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STUSoundStatics.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUSoundStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Sound")
    static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

    UFUNCTION(BlueprintCallable, Category = "Sound")
    static void ToggleSoundClassVolume(USoundClass* SoundClass);
    
};
