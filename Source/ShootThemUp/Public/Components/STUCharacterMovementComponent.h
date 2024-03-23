// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    virtual float GetMaxSpeed() const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MaxSprintSpeed = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FVector2D LandedVelocity = FVector2D(600.0f, 1200.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
