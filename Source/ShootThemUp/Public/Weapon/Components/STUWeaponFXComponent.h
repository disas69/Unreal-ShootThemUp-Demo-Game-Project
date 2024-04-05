// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/STUWeapon.h"
#include "STUWeaponFXComponent.generated.h"

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

private:
    UPROPERTY()
    USkeletalMeshComponent* WeaponMesh = nullptr;
    
    FName MuzzleSocketName = "";

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent = nullptr;
    
    UNiagaraComponent* SpawnMuzzleFX(USkeletalMeshComponent* Mesh, const FName& SocketName) const;
    void SetMuzzleFXActive(bool IsActive);
};
