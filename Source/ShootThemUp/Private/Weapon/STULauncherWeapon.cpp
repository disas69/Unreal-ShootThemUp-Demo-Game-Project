// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

void ASTULauncherWeapon::StartFire()
{
    Super::StartFire();
    FireInternal();
}

void ASTULauncherWeapon::StopFire()
{
    Super::StopFire();
}

void ASTULauncherWeapon::FireInternal()
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
    
    FVector ShootDirection = (TraceEndLocation - SocketLocation).GetSafeNormal();
    ASTUProjectile* Projectile = GetWorld()->SpawnActor<ASTUProjectile>(ProjectileClass, SocketTransform);
    if (Projectile != nullptr)
    {
        Projectile->SetOwner(GetOwner());
        Projectile->Launch(ShootDirection, Damage, DamageRadius);
    }

    WeaponFXComponent->PlayFireSound();
    DecreaseAmmo();
}
