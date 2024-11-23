// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUGamePauseWidget.h"
#include "STUGameInstance.h"
#include "STUGameModeBase.h"
#include "Components/Button.h"
#include "UI/STUButtonWidget.h"

bool USTUGamePauseWidget::Initialize()
{
    const bool bInit = Super::Initialize();
    return bInit;
}

void USTUGamePauseWidget::SetVisibility(ESlateVisibility InVisibility)
{
    Super::SetVisibility(InVisibility);

    if (InVisibility == ESlateVisibility::Visible)
    {
        ContinueButton->SetFocus(true);
    }
}

void USTUGamePauseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ContinueButton->Get() != nullptr)
    {
        ContinueButton->Get()->OnClicked.AddDynamic(this, &USTUGamePauseWidget::ContinueGame);
    }

    if (ExitButton->Get() != nullptr)
    {
        ExitButton->Get()->OnClicked.AddDynamic(this, &USTUGamePauseWidget::ExitGame);
    }
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