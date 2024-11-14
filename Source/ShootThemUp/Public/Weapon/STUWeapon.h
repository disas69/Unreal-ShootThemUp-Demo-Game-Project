// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUWeapon.generated.h"

class ASTUBaseCharacter;
class USTUWeaponFXComponent;
class ASTUGameHUD;
class ASTUWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmpty, ASTUWeapon*);

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!bIsUnlimited"))
    int32 Clips;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    bool bIsUnlimited = false;
};

USTRUCT(BlueprintType)
struct FWeaponImageData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UTexture2D* PreviewImage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairImage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    float CrossHairScale = 1.0f;
};

UCLASS()
class SHOOTTHEMUP_API ASTUWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUWeapon();

    FOnClipEmpty OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire();
    void Reload();
    bool IsFullAmmo() const;
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    bool CanReload() const;

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    FAmmoData& GetDefaultAmmoData() { return DefaultAmmo; }

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    FAmmoData& GetCurrentAmmoData() { return CurrentAmmo; }

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    FWeaponImageData& GetWeaponImageData() { return WeaponImageData; }

    bool AddAmmo(int32 ClipsAmount);
    void OnEquipFinished();

    virtual void Aim(bool bAiming);

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
    float AimCameraFOV = 60.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
    float AimSensitivity = 0.6f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FWeaponImageData WeaponImageData;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    USTUWeaponFXComponent* WeaponFXComponent = nullptr;
    
    virtual void BeginPlay() override;
    virtual void FireInternal();
    
    void TraceWeapon(const FVector& SocketLocation, FHitResult& HitResult, FVector& TraceEndLocation);
    void ApplyDamage(const FHitResult& HitResult, const FDamageEvent& DamageEvent);
    FTransform GetMuzzleSocketTransform() const;

    void DecreaseAmmo();

private:
    UPROPERTY()
    ASTUBaseCharacter* Character = nullptr;

    UPROPERTY()
    AController* Controller = nullptr;

    UPROPERTY()
    UCameraShakeBase* CurrentCameraShake = nullptr;

    FAmmoData CurrentAmmo;

    void GetPlayerViewPoint(FVector& Location, FRotator& Rotation);
    AController* GetPlayerController();

    void StartCameraShake(TSubclassOf<UCameraShakeBase> CameraShake, bool bIsSingleInstance = false);
    void StopCameraShake(UCameraShakeBase* CameraShakeInstance);
};
