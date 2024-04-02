// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"

ASTUWeapon::ASTUWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUWeapon::BeginPlay()
{
    Super::BeginPlay();
    Character = Cast<ACharacter>(GetOwner());
    CurrentAmmo = DefaultAmmo;
}

void ASTUWeapon::StartFire() {}

void ASTUWeapon::StopFire() {}

void ASTUWeapon::FireInternal() {}

void ASTUWeapon::TraceWeapon(const FVector& SocketLocation, FHitResult& HitResult, FVector& TraceEndLocation)
{
    FVector ViewLocation;
    FRotator ViewDirection;
    GetPlayerController()->GetPlayerViewPoint(ViewLocation, ViewDirection);

    // Trace from the crosshair to the target location
    const FVector StartLocation = ViewLocation;
    const FVector Direction = FMath::VRandCone(ViewDirection.Vector(), FMath::DegreesToRadians(BulletSpread));
    const FVector EndLocation = StartLocation + Direction * Range;
    TraceEndLocation = EndLocation;

    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(Character);
    CollisionQueryParams.bReturnPhysicalMaterial = true;

    FHitResult ScreenTraceResult;
    if (Character->GetWorld()->LineTraceSingleByChannel(ScreenTraceResult, StartLocation, EndLocation, ECC_Visibility, CollisionQueryParams))
    {
        HitResult = ScreenTraceResult;
        TraceEndLocation = ScreenTraceResult.ImpactPoint;
    }

    // Trace from the weapon to the target location to ensure there's no blocking object in between
    FHitResult WeaponTraceResult;
    if (Character->GetWorld()->LineTraceSingleByChannel(WeaponTraceResult, SocketLocation, TraceEndLocation, ECC_Visibility, CollisionQueryParams))
    {
        HitResult = WeaponTraceResult;
        TraceEndLocation = WeaponTraceResult.ImpactPoint;
    }
}

void ASTUWeapon::ApplyDamage(const FHitResult& HitResult)
{
    if (HitResult.bBlockingHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor != nullptr)
        {
            HitActor->TakeDamage(Damage, FDamageEvent(), GetPlayerController(), this);
            UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *HitActor->GetName());
        }
    }
}

FTransform ASTUWeapon::GetMuzzleSocketTransform() const
{
    return WeaponMesh->GetSocketTransform(MuzzleSocketName);
}

void ASTUWeapon::DecreaseAmmo()
{
    CurrentAmmo.Bullets = FMath::Max(CurrentAmmo.Bullets - 1, 0);
    
    if (IsClipEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

bool ASTUWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.bIsUnlimited && CurrentAmmo.Clips == 0 && CurrentAmmo.Bullets == 0;
}

bool ASTUWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

bool ASTUWeapon::CanReload() const
{
    return (CurrentAmmo.bIsUnlimited || CurrentAmmo.Clips > 0) && CurrentAmmo.Bullets < DefaultAmmo.Bullets;
}

bool ASTUWeapon::AddAmmo(int32 ClipsAmount)
{
    if (CurrentAmmo.bIsUnlimited || CurrentAmmo.Clips == DefaultAmmo.Clips)
    {
        return false;
    }

    if (IsAmmoEmpty())
    {
        CurrentAmmo.Clips = ClipsAmount;
        OnClipEmpty.Broadcast(this);
    }
    else
    {
        CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips);
    }
    
    return true;
}

void ASTUWeapon::Reload()
{
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;

    if (!CurrentAmmo.bIsUnlimited)
    {
        CurrentAmmo.Clips = FMath::Max(CurrentAmmo.Clips - 1, 0);
    }
}

bool ASTUWeapon::IsFullAmmo() const
{
    return CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

APlayerController* ASTUWeapon::GetPlayerController()
{
    if (Controller == nullptr)
    {
        Controller = Character->GetController<APlayerController>();
    }

    return Controller;
}
