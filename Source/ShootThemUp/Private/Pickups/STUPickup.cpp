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

    UE_LOG(LogTemp, Display, TEXT("Pickup overlapped with %s"), *OtherActor->GetName());
    Destroy();
}

void ASTUPickup::BeginPlay()
{
    Super::BeginPlay();
}
