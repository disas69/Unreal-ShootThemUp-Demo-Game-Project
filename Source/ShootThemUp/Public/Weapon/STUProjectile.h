// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USTUWeaponFXComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
    GENERATED_BODY()

public:
    ASTUProjectile();

    void Launch(const FVector& LaunchDirection, float Damage, float Radius);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    USphereComponent* SphereComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    UProjectileMovementComponent* MovementComponent = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float LifeSpanSeconds = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
    TSubclassOf<AActor> AutoAimTargetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
    float AutoAimDistance = 3000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
    float AutoAimRadius = 100.0f;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    USTUWeaponFXComponent* WeaponFXComponent = nullptr;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    virtual void BeginPlay() override;

private:
    FVector MoveDirection = FVector::ZeroVector;
    float DamageAmount = 0.0f;
    float DamageRadius = 0.0f;

    AController* GetOwnerController() const;
    USceneComponent* TryGetHomingTarget() const;
};
