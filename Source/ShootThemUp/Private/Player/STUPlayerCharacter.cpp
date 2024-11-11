// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Player/STUPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/InputDataConfig.h"
#include "Weapon/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/STUAimAssistComponent.h"
#include "Components/STUCameraZoomComponent.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    CameraCollision = CreateDefaultSubobject<USphereComponent>("CameraCollision");
    CameraCollision->SetupAttachment(Camera);
    CameraCollision->SetSphereRadius(10.0f);
    CameraCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    CameraZoomComponent = CreateDefaultSubobject<USTUCameraZoomComponent>("CameraZoomComponent");
    AimAssistComponent = CreateDefaultSubobject<USTUAimAssistComponent>("AimAssistComponent");
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    const APlayerController* PlayerController = Cast<APlayerController>(GetController());
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputDataConfig->InputMappingContext, 0);

    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    Input->BindAction(InputDataConfig->Move, ETriggerEvent::Triggered, this, &ASTUPlayerCharacter::Move);
    Input->BindAction(InputDataConfig->Look, ETriggerEvent::Triggered, this, &ASTUPlayerCharacter::Look);
    Input->BindAction(InputDataConfig->Jump, ETriggerEvent::Triggered, this, &ASTUBaseCharacter::Jump);
    Input->BindAction(InputDataConfig->Sprint, ETriggerEvent::Triggered, this, &ASTUPlayerCharacter::Sprint);
    Input->BindAction(InputDataConfig->Fire, ETriggerEvent::Triggered, this, &ASTUPlayerCharacter::Fire);
    Input->BindAction(InputDataConfig->Aim, ETriggerEvent::Triggered, this, &ASTUPlayerCharacter::Aim);
    Input->BindAction(InputDataConfig->SwitchWeapon, ETriggerEvent::Triggered, WeaponComponent, &USTUWeaponComponent::SwitchWeapon);
    Input->BindAction(InputDataConfig->Reload, ETriggerEvent::Triggered, WeaponComponent, &USTUWeaponComponent::Reload);
}

void ASTUPlayerCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    const FRotator CameraRotation = Camera->GetComponentRotation();
    const FRotator CameraYawRotation(0, CameraRotation.Yaw, 0);

    // Get the forward direction based on the camera orientation and apply movement
    const FVector ForwardDirection = FRotationMatrix(CameraYawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardDirection, MovementVector.Y);

    // Get the right direction based on the camera orientation and apply movement
    const FVector RightDirection = FRotationMatrix(CameraYawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(RightDirection, MovementVector.X);

    bIsMovingForward = MovementVector.Y > 0.0f && FMath::Abs(MovementVector.X) < 0.7f;
}

void ASTUPlayerCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();
    float Sensitivity = CameraZoomComponent->GetCameraSensitivity();

    if (bIsGamepadInputEnabled)
    {
        const float TurnAmount = LookAxisVector.X * CameraGamepadRotationRate * Sensitivity * GetWorld()->GetDeltaSeconds();
        AddControllerYawInput(TurnAmount);
    
        const float LookAmount = LookAxisVector.Y * CameraGamepadRotationRate * Sensitivity * GetWorld()->GetDeltaSeconds();
        AddControllerPitchInput(LookAmount);
    }
    else
    {
        Sensitivity *= CameraMouseSensitivityMultiplier;
        AddControllerYawInput(LookAxisVector.X * Sensitivity);
        AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
    }
}

void ASTUPlayerCharacter::Sprint(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        StartSprint();
    }
    else
    {
        StopSprint();
    }
}

void ASTUPlayerCharacter::Fire(const FInputActionValue& Value)
{
    if (Value.Get<bool>())
    {
        StartFire();
    }
    else
    {
        StopFire();
    }
}

void ASTUPlayerCharacter::Aim(const FInputActionValue& Value)
{
    const bool bIsAiming = Value.Get<bool>();
    
    if (WeaponComponent != nullptr)
    {
        WeaponComponent->Aim(bIsAiming);
    }

    if (AimAssistComponent != nullptr)
    {
        AimAssistComponent->SetIsAiming(bIsAiming);
    }
}

void ASTUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UpdateCameraCollision();
}

void ASTUPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    UpdateCameraCollision();
}

void ASTUPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    CameraCollision->OnComponentBeginOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollision->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionEndOverlap);
}

void ASTUPlayerCharacter::OnHealthChanged(float NewHealth, float HealthDelta)
{
    Super::OnHealthChanged(NewHealth, HealthDelta);

    if (HealthComponent->IsAlive() && HealthDelta < 0.0f)
    {
        PlayCameraShake(DamageCameraShake);
    }
}

void ASTUPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    
    CameraZoomComponent->ResetCameraFOV();

    if (Controller != nullptr)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUPlayerCharacter::StartSprint()
{
    Super::StartSprint();
    CameraZoomComponent->ZoomIn(SprintCameraFOV);
}

void ASTUPlayerCharacter::StopSprint()
{
    Super::StopSprint();
    CameraZoomComponent->ZoomOut();
}

void ASTUPlayerCharacter::StopPlayer()
{
    Super::StopPlayer();
    WeaponComponent->Aim(false);
}

void ASTUPlayerCharacter::PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake) const
{
    const APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController != nullptr && PlayerController->PlayerCameraManager != nullptr)
    {
        PlayerController->PlayerCameraManager->StartCameraShake(CameraShake);
    }
}

void ASTUPlayerCharacter::UpdateCameraCollision() const
{
    const bool bIsOverlapping = CameraCollision->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(bIsOverlapping);

    TArray<USceneComponent*> ChildrenComponents;
    GetMesh()->GetChildrenComponents(true, ChildrenComponents);

    for (USceneComponent* Component : ChildrenComponents)
    {
        UMeshComponent* MeshComponent = Cast<UMeshComponent>(Component);
        if (MeshComponent != nullptr)
        {
            MeshComponent->SetOwnerNoSee(bIsOverlapping);
        }
    }
}
