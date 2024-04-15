// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuWidget.h"
#include "STUGameInstance.h"
#include "Components/Button.h"

bool USTUMenuWidget::Initialize()
{
    const bool bResult = Super::Initialize();
    if (StartGameButton != nullptr)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::StartGame);
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