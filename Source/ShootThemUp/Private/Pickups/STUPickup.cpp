// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Pickups/STUPickup.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASTUPickup::ASTUPickup()
{
    PrimaryActorTick.bCanEverTick = true;

    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->InitSphereRadius(50.0f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(SphereComponent);
}

void ASTUPickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    CurrentLocation.Z = InitialLocation.Z + FloatingOffset * FMath::Sin(FloatingSpeed * GetWorld()->TimeSeconds);
    SetActorLocation(CurrentLocation);

    FRotator CurrentRotation = GetActorRotation();
    CurrentRotation.Yaw += RotationRate * DeltaTime;
    SetActorRotation(CurrentRotation);
}

void ASTUPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if (OtherPawn != nullptr && TryCollectPickup(OtherPawn))
    {
        Collect();
    }
}

void ASTUPickup::BeginPlay()
{
    Super::BeginPlay();
    InitialLocation = GetActorLocation();
}

bool ASTUPickup::TryCollectPickup(APawn* CollectorPawn)
{
    return false;
}

void ASTUPickup::Collect()
{
    bIsAvailable = false;
    GetRootComponent()->SetVisibility(false, true);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUPickup::Respawn, RespawnTime, false);
}

void ASTUPickup::Respawn()
{
    bIsAvailable = true;
    GetRootComponent()->SetVisibility(true, true);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}
