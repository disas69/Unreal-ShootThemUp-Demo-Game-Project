// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    UNiagaraSystem* ImpactEffect = DefaultImpactEffect;

    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* PhysMaterial = Hit.PhysMaterial.Get();
        if (ImpactEffects.Contains(PhysMaterial))
        {
            ImpactEffect = ImpactEffects[PhysMaterial];
        }
    }
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
