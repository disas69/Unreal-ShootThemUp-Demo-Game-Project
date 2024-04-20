// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCameraZoomComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUCameraZoomComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUCameraZoomComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float CameraFOV = 75.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float CameraSensitivity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float ZoomSpeed = 5.0f;

    float GetCameraSensitivity() const { return CameraSensitivity; }
    void SetCameraSensitivity(float NewSensitivity) { CameraSensitivity = NewSensitivity; }
    void ResetCameraSensitivity() { CameraSensitivity = DefaultCameraSensitivity; }
    void ResetCameraFOV();

    void ZoomIn(float TargetFOV);
    void ZoomOut();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
    bool bZooming = false;
    float DefaultFieldOfView = 0.0f;
    float TargetFieldOfView = 0.0f;
    float DefaultCameraSensitivity = 0.0f;

    UPROPERTY()
    APlayerCameraManager* PlayerCameraManager = nullptr;

    APlayerCameraManager* GetPlayerCameraManager() const;
};
