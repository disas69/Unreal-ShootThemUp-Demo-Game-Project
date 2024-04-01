// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Pickups/STUPickup.h"
#include "Components/SphereComponent.h"

ASTUPickup::ASTUPickup()
{
    PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->InitSphereRadius(50.0f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(SphereComponent);
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
}

bool ASTUPickup::TryCollectPickup(APawn* CollectorPawn)
{
    return false;
}

void ASTUPickup::Collect()
{
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUPickup::Respawn, RespawnTime, false);
}

void ASTUPickup::Respawn() const
{
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}
