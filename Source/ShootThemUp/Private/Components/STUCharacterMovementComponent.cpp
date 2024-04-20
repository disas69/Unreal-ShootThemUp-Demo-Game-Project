// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STUCharacterMovementComponent.h"

#include "Engine/DamageEvents.h"
#include "Player/STUBaseCharacter.h"

void USTUCharacterMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    ACharacter* Character = GetCharacterOwner();
    if (Character != nullptr)
    {
        Character->LandedDelegate.AddDynamic(this, &USTUCharacterMovementComponent::OnGroundLanded);
    }
}

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();

    const ASTUBaseCharacter* Character = Cast<ASTUBaseCharacter>(GetCharacterOwner());
    if (Character != nullptr && Character->IsSprintingForward())
    {
        return MaxSprintSpeed;
    }

    return MaxSpeed;
}

void USTUCharacterMovementComponent::OnGroundLanded(const FHitResult& Hit)
{
    const float FallVelocity = -Velocity.Z;

    if (FallVelocity > LandedVelocity.X)
    {
        const float Damage = FMath::GetMappedRangeValueClamped(LandedVelocity, LandedDamage, FallVelocity);
        GetCharacterOwner()->TakeDamage(Damage, FPointDamageEvent(), nullptr, nullptr);
    }
}
