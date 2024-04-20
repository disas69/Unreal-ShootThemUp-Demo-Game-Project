// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/STUWeapon.h"
#include "STUWeaponFXComponent.generated.h"

class USoundCue;
class UNiagaraComponent;
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UMaterial* Material = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FVector Size = FVector(10.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float LifeTime = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* Effect = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* Sound = nullptr;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUWeaponFXComponent();

    void Initialize(USkeletalMeshComponent* Mesh, FName SocketName);
    void PlayFireFX();
    void StopFireFX();
    void PlayTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
    void PlayImpactFX(const FHitResult& Hit);

    void PlayAmmoEmptySound();
    void PlayFireSound();
    void StopFireSound();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FImpactData DefaultImpactEffectData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TMap<UPhysicalMaterial*, FImpactData> ImpactEffectsData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFX = nullptr;

    UPROPERTY(EditAnywhere, Category = "VFX")
    UNiagaraSystem* TraceFX = nullptr;

    UPROPERTY(EditAnywhere, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
    USoundCue* FireSound = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
    USoundCue* NoAmmoSound = nullptr;

private:
    UPROPERTY()
    USkeletalMeshComponent* WeaponMesh = nullptr;
    
    FName MuzzleSocketName = "";

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent = nullptr;

    UPROPERTY()
    UAudioComponent* FireSoundComponent = nullptr;
    
    void SetMuzzleFXActive(bool IsActive);
};
