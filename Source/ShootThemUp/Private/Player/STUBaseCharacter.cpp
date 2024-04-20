// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Player/STUBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapon/STUWeaponComponent.h"

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = true;
    bUseControllerRotationRoll = false;

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    bIsSprinting = false;
    bIsMovingForward = false;

    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    WeaponComponent->Initialize();
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Stop sprinting if the character is firing
    if (bIsSprinting && bIsFireInProgress)
    {
        StopSprint();
    }

    // Try to start firing if there's pending player input
    if (bIsFireInProgress && !WeaponComponent->IsFireInProgress())
    {
        WeaponComponent->StartFire();
    }
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

void ASTUBaseCharacter::SetPlayerColor(FLinearColor TeamColor) const
{
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    if (CharacterMesh != nullptr)
    {
        UMaterialInstanceDynamic* MaterialInstance = CharacterMesh->CreateAndSetMaterialInstanceDynamic(0);
        if (MaterialInstance != nullptr)
        {
            MaterialInstance->SetVectorParameterValue(ColorParameterName, TeamColor);
        }
    }
}

void ASTUBaseCharacter::StartSprint()
{
    if (WeaponComponent->IsFireInProgress())
    {
        return;
    }

    bIsSprinting = true;
    WeaponComponent->Aim(false);
}

void ASTUBaseCharacter::StopSprint()
{
    bIsSprinting = false;
}

void ASTUBaseCharacter::StartFire()
{
    bIsFireInProgress = true;
    WeaponComponent->StartFire();
}

void ASTUBaseCharacter::StopFire()
{
    bIsFireInProgress = false;
    WeaponComponent->StopFire();
}

void ASTUBaseCharacter::OnHealthChanged(float NewHealth, float HealthDelta)
{
    
}

void ASTUBaseCharacter::OnDeath()
{
    StopFire();
    DisableInput(nullptr);
    GetCharacterMovement()->DisableMovement();
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    PlayAnimMontage(DeathAnimation);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());

    FTimerHandle DeathTimerHandle;
    GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ASTUBaseCharacter::EnableRagdollPhysics, DeathAnimation->GetPlayLength() * FMath::RandRange(0.0f, 0.5f), false);
}

void ASTUBaseCharacter::EnableRagdollPhysics() const
{
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    if (CharacterMesh != nullptr)
    {
        CharacterMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        CharacterMesh->SetSimulatePhysics(true);
    }
}
