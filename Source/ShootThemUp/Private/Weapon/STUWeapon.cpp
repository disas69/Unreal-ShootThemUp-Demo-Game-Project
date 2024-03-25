// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
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

void ASTUWeapon::Fire()
{
    FireSingle();
}

void ASTUWeapon::FireSingle()
{
    FVector ViewLocation;
    FRotator ViewDirection;
    GetPlayerController()->GetPlayerViewPoint(ViewLocation, ViewDirection);

    // Trace from the crosshair to the target location
    const FVector StartLocation = ViewLocation;
    const FVector EndLocation = StartLocation + ViewDirection.Vector() * FireRange;
    FVector TraceEndLocation = EndLocation;

    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(Character);

    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector SocketLocation = SocketTransform.GetLocation();

    FHitResult HitResult;
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

    DrawDebugLine(GetWorld(), SocketLocation, TraceEndLocation, FColor::Red, false, 2.0f, 0, 2.0f);

    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f, 0, 2.0f);

        AActor* HitActor = HitResult.GetActor();
        if (HitActor != nullptr)
        {
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
