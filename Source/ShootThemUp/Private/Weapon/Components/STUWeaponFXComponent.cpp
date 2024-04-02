// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
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

    UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactEffectData.DecalData.Material, ImpactEffectData.DecalData.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
    if (Decal != nullptr)
    {
        Decal->SetFadeOut(ImpactEffectData.DecalData.LifeTime, ImpactEffectData.DecalData.FadeOutTime);
    }
}
