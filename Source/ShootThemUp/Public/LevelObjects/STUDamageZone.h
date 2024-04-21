// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDamageZone.generated.h"

class UBoxComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUDamageZone : public AActor
{
    GENERATED_BODY()

public:
    ASTUDamageZone();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* BoxComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    float Damage = 1000.0f;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
