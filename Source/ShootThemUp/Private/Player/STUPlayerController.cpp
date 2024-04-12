// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
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

void ASTUPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    ASTUBaseCharacter* NewCharacterPawn = Cast<ASTUBaseCharacter>(InPawn);
    if (NewCharacterPawn != nullptr)
    {
        CharacterPawn = NewCharacterPawn;
    }
}