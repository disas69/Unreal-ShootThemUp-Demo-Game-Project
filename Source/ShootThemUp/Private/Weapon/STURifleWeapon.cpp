// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STURifleWeapon.h"

#include "Components/TimelineComponent.h"
#include "Engine/DamageEvents.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

void ASTURifleWeapon::StartFire()
{
    Super::StartFire();
    GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASTURifleWeapon::FireInternal, Rate, true);
    FireInternal();
}

void ASTURifleWeapon::StopFire()
{
    Super::StopFire();
    GetWorldTimerManager().ClearTimer(FireTimerHandle);
    WeaponFXComponent->StopFireSound();
}

void ASTURifleWeapon::FireInternal()
{
    Super::FireInternal();

    if (IsAmmoEmpty())
    {
        WeaponFXComponent->PlayAmmoEmptySound();
        StopFire();
        return;
    }

    const FTransform SocketTransform = GetMuzzleSocketTransform();
    const FVector SocketLocation = SocketTransform.GetLocation();

    FHitResult HitResult;
    FVector TraceEndLocation;
    TraceWeapon(SocketLocation, HitResult, TraceEndLocation);

    WeaponFXComponent->PlayTraceFX(SocketLocation, TraceEndLocation);
    WeaponFXComponent->PlayFireSound();

    if (HitResult.bBlockingHit)
    {
        WeaponFXComponent->PlayImpactFX(HitResult);
    }

    RecoilTimeline->PlayFromStart();

    FPointDamageEvent DamageEvent;
    DamageEvent.HitInfo = HitResult;
    ApplyDamage(HitResult, DamageEvent);

    DecreaseAmmo();
}
