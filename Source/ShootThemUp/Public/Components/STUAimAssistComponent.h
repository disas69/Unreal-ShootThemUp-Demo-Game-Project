// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUAimAssistComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUAimAssistComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUAimAssistComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Assist")
    FVector AimOffset = FVector(0.0f, 0.0f, 30.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Assist")
    float TraceDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Assist")
    float TraceRadius = 25.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Assist")
    float SnapSpeed = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim Assist")
    TSubclassOf<AActor> TargetClass;

    FORCEINLINE void SetIsAiming(bool IsAiming) { bIsAiming = IsAiming; }
    FORCEINLINE void SetTargetPredicate(TFunction<bool(AActor*)> Predicate) { TargetPredicate = Predicate; }

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    virtual void BeginPlay() override;

private:
    bool bIsAiming = false;
    TFunction<bool(AActor*)> TargetPredicate = nullptr;

    void AssistAim() const;
    AActor* SphereTraceForTarget() const;
};
