// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "LevelObjects/STULevelBounds.h"
#include "Components/BoxComponent.h"
#include "Player/STUBaseCharacter.h"

ASTULevelBounds::ASTULevelBounds()
{
    PrimaryActorTick.bCanEverTick = true;

    BoundsComponent = CreateDefaultSubobject<UBoxComponent>("BoundsComponent");
    BoundsComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoundsComponent->SetCollisionObjectType(ECC_Pawn);
    SetRootComponent(BoundsComponent);
}

void ASTULevelBounds::BeginPlay()
{
    Super::BeginPlay();
    BoundsComponent->OnComponentBeginOverlap.AddDynamic(this, &ASTULevelBounds::OnBoundsBeginOverlap);
    BoundsComponent->OnComponentEndOverlap.AddDynamic(this, &ASTULevelBounds::OnBoundsEndOverlap);
}

void ASTULevelBounds::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASTULevelBounds::OnBoundsBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(OtherActor);
    if (Player != nullptr)
    {
        Player->SetInsideLevelBounds(true);
    }
}

void ASTULevelBounds::OnBoundsEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(OtherActor);
    if (Player != nullptr)
    {
        Player->SetInsideLevelBounds(false);
    }
}
