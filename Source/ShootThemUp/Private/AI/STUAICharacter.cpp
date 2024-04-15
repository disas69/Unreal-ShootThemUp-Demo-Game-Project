// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/STUHealthBarWidget.h"
#include "Weapon/STUAIWeaponComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTUAIController::StaticClass();

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);

    bUseControllerRotationYaw = false;

    UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
    if (CharacterMovementComponent != nullptr)
    {
        CharacterMovementComponent->bUseControllerDesiredRotation = true;
        CharacterMovementComponent->RotationRate = FRotator(0.0f, 250.0f, 0.0f);
    }
}

void ASTUAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateHealthWidgetVisibility();
}

void ASTUAICharacter::BeginPlay()
{
    Super::BeginPlay();
    UpdateHealthWidgetValue();
}

void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();

    const AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController != nullptr && AIController->BrainComponent != nullptr)
    {
        AIController->BrainComponent->Cleanup();
    }
}

void ASTUAICharacter::OnHealthChanged(float NewHealth, float HealthDelta)
{
    Super::OnHealthChanged(NewHealth, HealthDelta);
    UpdateHealthWidgetValue();
}

void ASTUAICharacter::UpdateHealthWidgetValue() const
{
    USTUHealthBarWidget* HealthBarWidget = Cast<USTUHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (HealthBarWidget != nullptr)
    {
        HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
    }
}

void ASTUAICharacter::UpdateHealthWidgetVisibility() const
{
    float Distance = MAX_FLT;
    
    if (HealthComponent->IsAlive())
    {
        const APlayerCameraManager* PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
        Distance = FVector::Distance(PlayerCamera->GetCameraLocation(), GetActorLocation());
    }

    USTUHealthBarWidget* HealthBarWidget = Cast<USTUHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (HealthBarWidget != nullptr)
    {
        HealthBarWidget->SetDistanceVisibility(Distance);
    }
}