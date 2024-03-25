// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUWeapon();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh = nullptr;
    
    virtual void BeginPlay() override;
};
