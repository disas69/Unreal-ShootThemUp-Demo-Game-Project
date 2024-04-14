// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUGamePauseWidget.h"
#include "STUGameModeBase.h"
#include "Components/Button.h"

bool USTUGamePauseWidget::Initialize()
{
    const bool bInit = Super::Initialize();

    if (ContinueButton != nullptr)
    {
        ContinueButton->OnClicked.AddDynamic(this, &USTUGamePauseWidget::ContinueGame);
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