// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
}