// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class USoundCue;
class USTUWeaponComponent;
class USTUHealthComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer);

    virtual void Tick(float DeltaTime) override;

    int32 GetTeamID() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsSprintingForward() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirectionAngle() const;

    void SetPlayerColor(FLinearColor TeamColor) const;

    void StartFire();
    void StopFire();

    virtual void StartSprint();
    virtual void StopSprint();
    virtual void StopPlayer();

    virtual void TurnOff() override;
    virtual void Reset() override;

protected:
    bool bIsMovingForward = false;

    UFUNCTION()
    virtual void OnHealthChanged(float NewHealth, float HealthDelta);

    UFUNCTION()
    virtual void OnDeath();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUHealthComponent* HealthComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUWeaponComponent* WeaponComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    UAnimMontage* DeathAnimation = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Material")
    FName ColorParameterName = "Paint Color";

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
    USoundCue* DeathSound = nullptr;

    virtual void BeginPlay() override;

private:
    bool bIsSprinting = false;
    bool bIsFireInProgress = false;

    void EnableRagdollPhysics() const;
};
