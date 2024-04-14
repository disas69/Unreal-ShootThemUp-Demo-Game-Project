// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "STUMenuGameModeBase.h"

#include "Menu/STUMenuHUD.h"
#include "Menu/STUMenuPlayerController.h"

ASTUMenuGameModeBase::ASTUMenuGameModeBase()
{
    PlayerControllerClass = ASTUMenuPlayerController::StaticClass();
    HUDClass = ASTUMenuHUD::StaticClass();
}