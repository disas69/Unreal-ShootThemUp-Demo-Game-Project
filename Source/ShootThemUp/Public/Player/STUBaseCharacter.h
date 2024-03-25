// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class ASTUWeapon;
class UTextRenderComponent;
class USTUHealthComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputDataConfig;
struct FInputActionValue;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsSprintingForward() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirectionAngle() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArm = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* Camera = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUHealthComponent* HealthComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* InputMappingContext = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputDataConfig* InputDataConfig = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    float CameraMovementRate = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    float CameraSensitivity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    UAnimMontage* DeathAnimation = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
    TSubclassOf<ASTUWeapon> WeaponClass;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    bool bIsSprinting = false;
    bool bIsMovingForward = false;

    UFUNCTION()
    void Move(const FInputActionValue& Value);

    UFUNCTION()
    void Look(const FInputActionValue& Value);

    void StartSprint();
    void StopSprint();

    UFUNCTION()
    void OnHealthChanged(float NewHealth);

    UFUNCTION()
    void OnDeath();

    void SpawnWeapon() const;
};
