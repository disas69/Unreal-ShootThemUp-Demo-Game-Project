// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STURifleWeapon.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFX = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFX");
}

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

    if (HitResult.bBlockingHit)
    {
        WeaponFX->PlayImpactFX(HitResult);
    }
    
    ApplyDamage(HitResult);
    DecreaseAmmo();
}
