// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Player/STUPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/STUHealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/InputDataConfig.h"
#include "Weapon/STUWeaponComponent.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    const APlayerController* PlayerController = Cast<APlayerController>(GetController());
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMappingContext, 0);

    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    Input->BindAction(InputDataConfig->Move, ETriggerEvent::Triggered, this, &ASTUPlayerCharacter::Move);
    Input->BindAction(InputDataConfig->Look, ETriggerEvent::Triggered, this, &ASTUPlayerCharacter::Look);
    Input->BindAction(InputDataConfig->Jump, ETriggerEvent::Triggered, this, &ASTUBaseCharacter::Jump);
    Input->BindAction(InputDataConfig->Sprint, ETriggerEvent::Started, this, &ASTUBaseCharacter::StartSprint);
    Input->BindAction(InputDataConfig->Sprint, ETriggerEvent::Completed, this, &ASTUBaseCharacter::StopSprint);
    Input->BindAction(InputDataConfig->Fire, ETriggerEvent::Started, this, &ASTUBaseCharacter::StartFire);
    Input->BindAction(InputDataConfig->Fire, ETriggerEvent::Completed, this, &ASTUBaseCharacter::StopFire);
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

    bIsMovingForward = MovementVector.Y > 0.0f && FMath::Abs(MovementVector.X) < 0.2f;
}

void ASTUPlayerCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    const float TurnAmount = LookAxisVector.X * CameraMovementRate * CameraSensitivity * GetWorld()->GetDeltaSeconds();
    AddControllerYawInput(TurnAmount);

    const float LookAmount = LookAxisVector.Y * CameraMovementRate * CameraSensitivity * GetWorld()->GetDeltaSeconds();
    AddControllerPitchInput(LookAmount);
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

    if (Controller != nullptr)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUPlayerCharacter::PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake) const
{
    const APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController != nullptr && PlayerController->PlayerCameraManager != nullptr)
    {
        PlayerController->PlayerCameraManager->StartCameraShake(CameraShake);
    }
}