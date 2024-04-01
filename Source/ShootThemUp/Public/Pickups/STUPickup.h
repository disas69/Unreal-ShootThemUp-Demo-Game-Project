// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUPickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPickup : public AActor
{
    GENERATED_BODY()

public:
    ASTUPickup();

    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* SphereComponent = nullptr;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
    virtual void BeginPlay() override;
};
