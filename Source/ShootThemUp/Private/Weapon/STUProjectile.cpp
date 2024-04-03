// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTUProjectile::ASTUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->InitSphereRadius(5.0f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
    SphereComponent->bReturnMaterialOnMove = true;
    SetRootComponent(SphereComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->bAutoActivate = false;

    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFX");
}

void ASTUProjectile::Launch(const FVector& LaunchDirection, float Damage, float Radius)
{
    MoveDirection = LaunchDirection;
    DamageAmount = Damage;
    DamageRadius = Radius;

    SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);

    MovementComponent->Velocity = MoveDirection * MovementComponent->InitialSpeed;
    MovementComponent->Activate();

    SetLifeSpan(LifeSpanSeconds);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    MovementComponent->StopMovementImmediately();
    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, nullptr, TArray<AActor*>(), this, nullptr, false);

    // DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 2.0f, 0, 2.0f);
    WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}

void ASTUProjectile::BeginPlay()
{
    Super::BeginPlay();
    SphereComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
}

APlayerController* ASTUProjectile::GetPlayerController()
{
    if (Controller == nullptr)
    {
        Controller = Cast<APawn>(GetOwner())->GetController<APlayerController>();
    }

    return Controller;
}
