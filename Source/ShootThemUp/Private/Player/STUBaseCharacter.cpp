// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Input/InputDataConfig.h"
#include "Weapon/STUWeaponComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    bIsSprinting = false;
    bIsMovingForward = false;

    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    WeaponComponent->Initialize();
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Stop sprinting if the character is firing
    if (bIsSprinting && WeaponComponent->IsFireInProgress())
    {
        StopSprint();
    }
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    const APlayerController* PlayerController = Cast<APlayerController>(GetController());

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMappingContext, 0);

    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    Input->BindAction(InputDataConfig->Move, ETriggerEvent::Triggered, this, &ASTUBaseCharacter::Move);
    Input->BindAction(InputDataConfig->Look, ETriggerEvent::Triggered, this, &ASTUBaseCharacter::Look);
    Input->BindAction(InputDataConfig->Jump, ETriggerEvent::Triggered, this, &ASTUBaseCharacter::Jump);
    Input->BindAction(InputDataConfig->Sprint, ETriggerEvent::Started, this, &ASTUBaseCharacter::StartSprint);
    Input->BindAction(InputDataConfig->Sprint, ETriggerEvent::Completed, this, &ASTUBaseCharacter::StopSprint);
    Input->BindAction(InputDataConfig->Fire, ETriggerEvent::Started, WeaponComponent, &USTUWeaponComponent::StartFire);
    Input->BindAction(InputDataConfig->Fire, ETriggerEvent::Completed, WeaponComponent, &USTUWeaponComponent::StopFire);
    Input->BindAction(InputDataConfig->SwitchWeapon, ETriggerEvent::Triggered, WeaponComponent, &USTUWeaponComponent::SwitchWeapon);
    Input->BindAction(InputDataConfig->Reload, ETriggerEvent::Triggered, WeaponComponent, &USTUWeaponComponent::Reload);
}

bool ASTUBaseCharacter::IsSprintingForward() const
{
    return bIsSprinting && bIsMovingForward && !GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetMovementDirectionAngle() const
{
    if (GetVelocity().IsZero())
    {
        return 0.0f;
    }

    const FVector Forward = GetActorForwardVector();
    const FVector VelocityNormal = GetVelocity().GetSafeNormal();

    // Calculate the angle between the forward vector and the velocity vector
    const float DotProduct = FVector::DotProduct(Forward, VelocityNormal);
    const float Angle = FMath::Acos(DotProduct);  // in radians

    // Calculate the direction of the angle
    const FVector CrossProduct = FVector::CrossProduct(Forward, VelocityNormal);
    const float Direction = FMath::Sign(CrossProduct.Z);

    // Convert the angle to degrees and multiply by the direction
    return FMath::RadiansToDegrees(Angle) * Direction;
}

void ASTUBaseCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();
    bIsMovingForward = MovementVector.Y > 0.0f && FMath::Abs(MovementVector.X) < 0.2f;

    const FRotator CameraRotation = Camera->GetComponentRotation();
    const FRotator CameraYawRotation(0, CameraRotation.Yaw, 0);

    // Get the forward direction based on the camera orientation and apply movement
    const FVector ForwardDirection = FRotationMatrix(CameraYawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardDirection, MovementVector.Y);

    // Get the right direction based on the camera orientation and apply movement
    const FVector RightDirection = FRotationMatrix(CameraYawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(RightDirection, MovementVector.X);
}

void ASTUBaseCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    const float TurnAmount = LookAxisVector.X * CameraMovementRate * CameraSensitivity * GetWorld()->GetDeltaSeconds();
    AddControllerYawInput(TurnAmount);

    const float LookAmount = LookAxisVector.Y * CameraMovementRate * CameraSensitivity * GetWorld()->GetDeltaSeconds();
    AddControllerPitchInput(LookAmount);
}

void ASTUBaseCharacter::StartSprint()
{
    if (WeaponComponent->IsFireInProgress())
    {
        return;
    }
    
    bIsSprinting = true;
}

void ASTUBaseCharacter::StopSprint()
{
    bIsSprinting = false;
}

void ASTUBaseCharacter::OnHealthChanged(float PreviousHealth, float NewHealth)
{
    if (HealthComponent->IsAlive() && NewHealth < PreviousHealth)
    {
        PlayCameraShake(DamageCameraShake);
    }
}

void ASTUBaseCharacter::OnDeath()
{
    DisableInput(nullptr);

    WeaponComponent->StopFire();
    GetCharacterMovement()->DisableMovement();
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    if (Controller != nullptr)
    {
        Controller->ChangeState(NAME_Spectating);
    }

    // PlayAnimMontage(DeathAnimation);

    USkeletalMeshComponent* CharacterMesh = GetMesh();
    if (CharacterMesh != nullptr)
    {
        CharacterMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        CharacterMesh->SetSimulatePhysics(true);
    }
}

void ASTUBaseCharacter::PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake)
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController != nullptr && PlayerController->PlayerCameraManager != nullptr)
    {
        PlayerController->PlayerCameraManager->StartCameraShake(CameraShake);
    }
}
