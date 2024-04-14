// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Player/STUPlayerController.h"
#include "EnhancedInputComponent.h"
#include "STUGameModeBase.h"
#include "Components/STURespawnComponent.h"
#include "Input/InputDataConfig.h"
#include "Player/STUBaseCharacter.h"

ASTUPlayerController::ASTUPlayerController()
{
    STURespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}

APawn* ASTUPlayerController::GetCharacterPawn()
{
    if (CharacterPawn == nullptr)
    {
        CharacterPawn = Cast<ASTUBaseCharacter>(GetPawn());
    }

    return CharacterPawn;
}

void ASTUPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode != nullptr)
    {
        GameMode->GameStateChanged.AddUObject(this, &ASTUPlayerController::OnGameStateChanged);
    }

    RotationInput = FRotator::ZeroRotator;
}

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ASTUBaseCharacter* NewCharacterPawn = Cast<ASTUBaseCharacter>(InPawn);
    if (NewCharacterPawn != nullptr)
    {
        CharacterPawn = NewCharacterPawn;
    }
}

void ASTUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
    if (Input != nullptr)
    {
        Input->BindAction(InputDataConfig->Pause, ETriggerEvent::Triggered, this, &ASTUPlayerController::OnGamePaused);
    }
}

void ASTUPlayerController::OnGameStateChanged(EGameState GameState)
{
    if (GameState == EGameState::Gameplay)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASTUPlayerController::OnGamePaused()
{
    ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode != nullptr)
    {
        GameMode->SetPause(this);
    }
}
