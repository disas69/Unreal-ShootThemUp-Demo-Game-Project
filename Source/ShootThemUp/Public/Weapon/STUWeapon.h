// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUWeapon.generated.h"

class ASTUGameHUD;

UCLASS()
class SHOOTTHEMUP_API ASTUWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUWeapon();

    virtual void Fire();
    void FireSingle();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    float FireRange = 10000.0f;
    
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ACharacter* Character = nullptr;

    UPROPERTY()
    APlayerController* Controller = nullptr;

    APlayerController* GetPlayerController();
};
