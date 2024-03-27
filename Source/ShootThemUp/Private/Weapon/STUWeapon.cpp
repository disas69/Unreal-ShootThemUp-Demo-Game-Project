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
}

void ASTUWeapon::StartFire()
{
    FireSingle();
    GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASTUWeapon::FireSingle, Rate, true);
}

void ASTUWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ASTUWeapon::FireSingle()
{
    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector SocketLocation = SocketTransform.GetLocation();
    
    FHitResult HitResult;
    FVector TraceEndLocation;
    TraceWeapon(SocketLocation, HitResult, TraceEndLocation);

    DrawDebugLine(GetWorld(), SocketLocation, TraceEndLocation, FColor::Red, false, 2.0f, 0, 2.0f);
    ApplyDamage(HitResult);
}

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

APlayerController* ASTUWeapon::GetPlayerController()
{
    if (Controller == nullptr)
    {
        Controller = Character->GetController<APlayerController>();
    }

    return Controller;
}
