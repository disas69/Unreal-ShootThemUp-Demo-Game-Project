// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STULevelBounds.generated.h"

class UBoxComponent;

UCLASS()
class SHOOTTHEMUP_API ASTULevelBounds : public AActor
{
    GENERATED_BODY()

public:
    ASTULevelBounds();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bounds")
    UBoxComponent* BoundsComponent;
    
    virtual void Tick(float DeltaTime) override;

protected:
    UFUNCTION()
    void OnBoundsBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnBoundsEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    virtual void BeginPlay() override;
};
