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

    virtual void StartFire();
    virtual void StopFire();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    USkeletalMeshComponent* WeaponMesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Damage = 35.0f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Range = 10000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Rate = 0.25f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;
    
    virtual void BeginPlay() override;
    virtual void FireInternal();
    
    void TraceWeapon(const FVector& SocketLocation, FHitResult& HitResult, FVector& TraceEndLocation);
    void ApplyDamage(const FHitResult& HitResult);

private:
    UPROPERTY()
    ACharacter* Character = nullptr;

    UPROPERTY()
    APlayerController* Controller = nullptr;

    APlayerController* GetPlayerController();
};
