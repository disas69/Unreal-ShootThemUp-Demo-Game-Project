// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "LevelObjects/STUDamageZone.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"

ASTUDamageZone::ASTUDamageZone()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
    SetRootComponent(BoxComponent);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
}

void ASTUDamageZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (OtherActor != nullptr)
    {
        const FPointDamageEvent DamageEvent;
        OtherActor->TakeDamage(Damage, DamageEvent, nullptr, this);
    }
}
