// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUGamePauseWidget.h"
#include "STUGameInstance.h"
#include "STUGameModeBase.h"
#include "Components/Button.h"

bool USTUGamePauseWidget::Initialize()
{
    const bool bInit = Super::Initialize();

    if (ContinueButton != nullptr)
    {
        ContinueButton->OnClicked.AddDynamic(this, &USTUGamePauseWidget::ContinueGame);
    }

    if (ExitButton != nullptr)
    {
        ExitButton->OnClicked.AddDynamic(this, &USTUGamePauseWidget::ExitGame);
    }

    return bInit;
}

void USTUGamePauseWidget::ContinueGame()
{
    ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode != nullptr)
    {
        GameMode->ClearPause();
    }
}

void USTUGamePauseWidget::ExitGame()
{
    USTUGameInstance* GameInstance = GetGameInstance<USTUGameInstance>();
    if (GameInstance != nullptr)
    {
        GameInstance->OpenMenuLevel();
    }
}