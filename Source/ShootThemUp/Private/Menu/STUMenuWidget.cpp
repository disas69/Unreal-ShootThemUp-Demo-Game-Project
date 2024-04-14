// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

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
    const FName LevelName = "TestLevel";
    UGameplayStatics::OpenLevel(this, LevelName);
}