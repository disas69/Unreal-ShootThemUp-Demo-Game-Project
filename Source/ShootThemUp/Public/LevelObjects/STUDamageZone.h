// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDamageZone.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDamageZone : public AActor
{
    GENERATED_BODY()

public:
    ASTUDamageZone();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* SceneComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    float Radius = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    float Damage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    FColor DebugColor = FColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
    bool bIsFullDamage = false;
    
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;
};
