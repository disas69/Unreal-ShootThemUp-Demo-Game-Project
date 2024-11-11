// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STUAimAssistComponent.h"
#include "Kismet/GameplayStatics.h"

USTUAimAssistComponent::USTUAimAssistComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USTUAimAssistComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USTUAimAssistComponent::AssistAim() const
{
    AActor* TargetActor = SphereTraceForTarget();
    if (TargetActor != nullptr)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PlayerController != nullptr)
        {
            FVector CameraLocation;
            FRotator CameraRotation;
            PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

            // Calculate the direction to the target based on the camera's view
            FVector TargetDirection = (TargetActor->GetActorLocation() + AimOffset - CameraLocation).GetSafeNormal();
            FRotator TargetRotation = TargetDirection.Rotation();

            // Smoothly interpolate control rotation toward the target
            FRotator NewControlRotation = FMath::RInterpTo(PlayerController->GetControlRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), SnapSpeed);
            PlayerController->SetControlRotation(NewControlRotation);
        }
    }
}

AActor* USTUAimAssistComponent::SphereTraceForTarget() const
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController == nullptr)
    {
        return nullptr;
    }

    FVector CameraLocation;
    FRotator CameraRotation;
    PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

    FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * TraceDistance);

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    
    // Perform sphere trace (swept sphere) for targets
    if (GetWorld()->SweepSingleByChannel(HitResult, CameraLocation, TraceEnd, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(TraceRadius), Params))
    {
        DrawDebugSphere(GetWorld(), HitResult.Location, TraceRadius, 12, FColor::Green, false, 0.1f);

        // Check if the hit actor is of the specified target class
        AActor* HitActor = HitResult.GetActor();
        if (HitActor != nullptr && HitActor->IsA(TargetClass))
        {
            return HitActor;
        }
    }

    DrawDebugSphere(GetWorld(), TraceEnd, TraceRadius, 12, FColor::Green, false, 0.1f);
    return nullptr;
}

void USTUAimAssistComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsAiming)
    {
        AssistAim();
    }
}
