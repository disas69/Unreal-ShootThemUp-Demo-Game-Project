// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuWidget.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

bool USTUMenuWidget::Initialize()
{
    const bool bResult = Super::Initialize();
    if (StartGameButton != nullptr)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::StartGame);
    }

    if (ExitGameButton != nullptr)
    {
        ExitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::ExitGame);
    }

    return bResult;
}

void USTUMenuWidget::StartGame()
{
    const USTUGameInstance* GameInstance = Cast<USTUGameInstance>(GetGameInstance());
    if (GameInstance != nullptr)
    {
        GameInstance->OpenGameLevel(0);
    }
}

void USTUMenuWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}