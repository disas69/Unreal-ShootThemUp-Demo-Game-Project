// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STURifleWeapon.h"
#include "Components/STUCameraZoomComponent.h"
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

void ASTURifleWeapon::Aim(bool bAiming)
{
    Super::Aim(bAiming);

    USTUCameraZoomComponent* CameraZoomComponent = GetOwner()->FindComponentByClass<USTUCameraZoomComponent>();
    if (CameraZoomComponent != nullptr)
    {
        if (bAiming)
        {
            CameraZoomComponent->ZoomIn(AimCameraFOV);
            CameraZoomComponent->SetCameraSensitivity(AimSensitivity);
        }
        else
        {
            CameraZoomComponent->ZoomOut();
            CameraZoomComponent->ResetCameraSensitivity();
        }
    }
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

    FPointDamageEvent DamageEvent;
    DamageEvent.HitInfo = HitResult;
    ApplyDamage(HitResult, DamageEvent);

    DecreaseAmmo();
}
