// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::Initialize(USkeletalMeshComponent* Mesh, FName SocketName)
{
    WeaponMesh = Mesh;
    MuzzleSocketName = SocketName;
}

void USTUWeaponFXComponent::PlayFireFX()
{
    if (!IsValid(MuzzleFXComponent))
    {
        MuzzleFXComponent = SpawnMuzzleFX(WeaponMesh, MuzzleSocketName);
    }
    
    SetMuzzleFXActive(true);
}

void USTUWeaponFXComponent::StopFireFX()
{
    SetMuzzleFXActive(false);
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    FImpactData ImpactEffectData = DefaultImpactEffectData;

    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.Get();
        if (ImpactEffectsData.Contains(PhysMaterial))
        {
            ImpactEffectData = ImpactEffectsData[PhysMaterial];
        }
    }

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffectData.Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

    UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(), ImpactEffectData.DecalData.Material, ImpactEffectData.DecalData.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
    if (Decal != nullptr)
    {
        Decal->SetFadeOut(ImpactEffectData.DecalData.LifeTime, ImpactEffectData.DecalData.FadeOutTime);
    }
}

void USTUWeaponFXComponent::PlayAmmoEmptySound()
{
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, GetOwner()->GetActorLocation());
}

void USTUWeaponFXComponent::PlayFireSound()
{
    if (!IsValid(FireSoundComponent))
    {
        FireSoundComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }

    FireSoundComponent->SetPaused(false);
}

void USTUWeaponFXComponent::StopFireSound()
{
    if (IsValid(FireSoundComponent))
    {
        FireSoundComponent->SetPaused(true);
    }
}

UNiagaraComponent* USTUWeaponFXComponent::SpawnMuzzleFX(USkeletalMeshComponent* Mesh, const FName& SocketName) const
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, Mesh, SocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}

void USTUWeaponFXComponent::SetMuzzleFXActive(bool IsActive)
{
    if (IsValid(MuzzleFXComponent))
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }
}

void USTUWeaponFXComponent::PlayTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    UNiagaraComponent* TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent != nullptr)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}
