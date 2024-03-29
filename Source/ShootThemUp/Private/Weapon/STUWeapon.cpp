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
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f, 0, 2.0f);

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
    
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        Reload();
    }

    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/" + FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogTemp, Display, TEXT("%s"), *AmmoInfo);
}

bool ASTUWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.bIsUnlimited && CurrentAmmo.Clips == 0 && CurrentAmmo.Bullets == 0;
}

bool ASTUWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

void ASTUWeapon::Reload()
{
    if (IsAmmoEmpty())
    {
        return;
    }

    CurrentAmmo.Bullets = DefaultAmmo.Bullets;

    if (!CurrentAmmo.bIsUnlimited)
    {
        CurrentAmmo.Clips = FMath::Max(CurrentAmmo.Clips - 1, 0);
    }

    UE_LOG(LogTemp, Display, TEXT("Reloaded"));
}

APlayerController* ASTUWeapon::GetPlayerController()
{
    if (Controller == nullptr)
    {
        Controller = Character->GetController<APlayerController>();
    }

    return Controller;
}
