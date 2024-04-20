// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"

class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputDataConfig;
struct FInputActionValue;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUBaseCharacter
{
    GENERATED_BODY()

public:
    ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer);

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArm = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* Camera = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CameraCollision = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputDataConfig* InputDataConfig = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    float CameraMovementRate = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    float CameraSensitivity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
    TSubclassOf<UCameraShakeBase> DamageCameraShake;

    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
    virtual void BeginPlay() override;
    virtual void OnHealthChanged(float NewHealth, float HealthDelta) override;
    virtual void OnDeath() override;

private:
    UFUNCTION()
    void Move(const FInputActionValue& Value);

    UFUNCTION()
    void Look(const FInputActionValue& Value);

    UFUNCTION()
    void Sprint(const FInputActionValue& Value);

    UFUNCTION()
    void Fire(const FInputActionValue& Value);

    void PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake) const;
    void UpdateCameraCollision() const;
};
