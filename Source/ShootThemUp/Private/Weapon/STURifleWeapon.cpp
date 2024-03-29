// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STURifleWeapon.h"

void ASTURifleWeapon::StartFire()
{
    Super::StartFire();
    FireInternal();
    GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASTURifleWeapon::FireInternal, Rate, true);
}

void ASTURifleWeapon::StopFire()
{
    Super::StopFire();
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

    DrawDebugLine(GetWorld(), SocketLocation, TraceEndLocation, FColor::Red, false, 2.0f, 0, 2.0f);
    ApplyDamage(HitResult);
    DecreaseAmmo();
}
