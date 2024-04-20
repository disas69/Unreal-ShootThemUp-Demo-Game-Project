// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUPickup.generated.h"

class USoundCue;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPickup : public AActor
{
    GENERATED_BODY()

public:
    ASTUPickup();

    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* SphereComponent = nullptr;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    float RespawnTime = 5.0f;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    float FloatingOffset = 100.0f;

    UPROPERTY(EditAnywhere, Category = "Pickup")
    float FloatingSpeed = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundCue* PickupSound = nullptr;

    bool IsAvailable() const { return bIsAvailable; }

    virtual void Tick(float DeltaTime) override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
    virtual void BeginPlay() override;
    virtual bool TryCollectPickup(APawn* CollectorPawn);

private:
    bool bIsAvailable = true;
    FVector InitialLocation = FVector::ZeroVector;
    
    void Collect();
    void Respawn();
};
