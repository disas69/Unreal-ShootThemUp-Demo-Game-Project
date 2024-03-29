// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"

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

    const FTransform SocketTransform = GetMuzzleSocketTransform();
    const FVector SocketLocation = SocketTransform.GetLocation();
    
    FHitResult HitResult;
    FVector TraceEndLocation;
    TraceWeapon(SocketLocation, HitResult, TraceEndLocation);

    DrawDebugLine(GetWorld(), SocketLocation, TraceEndLocation, FColor::Red, false, 2.0f, 0, 2.0f);

    FVector ShootDirection = (TraceEndLocation - SocketLocation).GetSafeNormal();
    ASTUProjectile* Projectile = GetWorld()->SpawnActor<ASTUProjectile>(ProjectileClass, SocketTransform);

    if (Projectile != nullptr)
    {
        Projectile->SetOwner(GetOwner());
        Projectile->Launch(ShootDirection, Damage, DamageRadius);
    }
}
