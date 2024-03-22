// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "LevelObjects/STUDamageZone.h"

#include "Kismet/GameplayStatics.h"

ASTUDamageZone::ASTUDamageZone()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
    SetRootComponent(SceneComponent);
}

void ASTUDamageZone::BeginPlay()
{
    Super::BeginPlay();
}

void ASTUDamageZone::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, DebugColor);

    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, TArray<AActor*>(), this, nullptr, bIsFullDamage);
}
