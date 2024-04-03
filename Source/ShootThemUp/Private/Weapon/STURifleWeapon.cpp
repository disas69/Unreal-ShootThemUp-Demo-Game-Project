// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STURifleWeapon.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFX");
}

void ASTURifleWeapon::StartFire()
{
    Super::StartFire();

    if (MuzzleFXComponent == nullptr)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    
    SetMuzzleFXActive(true);
    GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASTURifleWeapon::FireInternal, Rate, true);
    FireInternal();
}

void ASTURifleWeapon::StopFire()
{
    Super::StopFire();
    SetMuzzleFXActive(false);
    GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ASTURifleWeapon::FireInternal()
{
    Super::FireInternal();

    if (IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    const FTransform SocketTransform = GetMuzzleSocketTransform();
    const FVector SocketLocation = SocketTransform.GetLocation();

    FHitResult HitResult;
    FVector TraceEndLocation;
    TraceWeapon(SocketLocation, HitResult, TraceEndLocation);

    SpawnTraceFX(SocketLocation, TraceEndLocation);

    if (HitResult.bBlockingHit)
    {
        WeaponFXComponent->PlayImpactFX(HitResult);
    }

    ApplyDamage(HitResult);
    DecreaseAmmo();
}

void ASTURifleWeapon::SetMuzzleFXActive(bool IsActive)
{
    if (MuzzleFXComponent != nullptr)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    UNiagaraComponent* TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent != nullptr)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}
