// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UWidgetComponent;
class UBehaviorTree;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
    GENERATED_BODY()

public:
    ASTUAICharacter(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTree = nullptr;

    virtual void Tick(float DeltaTime) override;
    virtual void TurnOff() override;
    virtual void Reset() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent = nullptr;
    
    virtual void BeginPlay() override;
    virtual void OnDeath() override;
    virtual void OnHealthChanged(float NewHealth, float HealthDelta) override;

private:
    void UpdateHealthWidgetValue() const;
    void UpdateHealthWidgetVisibility() const;
    void CleanupBrainComponent() const;
};
