// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STUCharacterMovementComponent.h"

#include "Player/STUBaseCharacter.h"

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