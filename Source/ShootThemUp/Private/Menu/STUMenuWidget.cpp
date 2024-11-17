// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuWidget.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/STULevelItemWidget.h"
#include "Menu/STUMenuSettingsWidget.h"
#include "Sound/SoundCue.h"

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

    if (SettingsButton != nullptr)
    {
        SettingsButton->OnClicked.AddDynamic(this, &USTUMenuWidget::ShowSettings);
    }

    CreateLevelItems();

    if (LevelItemWidgets.Num() > 0)
    {
        OnLevelItemSelected(0);
        OnLevelItemFocused(0);
    }

    return bResult;
}

void USTUMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    GetWorld()->GetTimerManager().SetTimerForNextTick(
        [&]
        {
            if (LevelItemWidgets.Num() > 0)
            {
                OnLevelItemFocused(0);
            }

            StartGameButton->IsFocusable = true;
            StartGameButton->SetKeyboardFocus();
        });
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation == LoadingAnimation)
    {
        LoadSelectedLevel();
    }
}

void USTUMenuWidget::StartGame()
{
    if (IsAnimationPlaying(LoadingAnimation))
    {
        return;
    }

    PlayAnimation(LoadingAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void USTUMenuWidget::ExitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::ShowSettings()
{
    USTUMenuSettingsWidget* MenuSettingsWidget = CreateWidget<USTUMenuSettingsWidget>(GetWorld(), SettingsWidgetClass);
    if (MenuSettingsWidget != nullptr)
    {
        MenuSettingsWidget->AddToViewport();
        RemoveFromParent();
    }
}

void USTUMenuWidget::CreateLevelItems()
{
    if (LevelItemWidgetClass == nullptr || LevelItemsBox == nullptr)
    {
        return;
    }

    LevelItemsBox->ClearChildren();

    const USTUGameInstance* GameInstance = GetGameInstance<USTUGameInstance>();
    if (GameInstance != nullptr)
    {
        const TArray<FLevelData>& Levels = GameInstance->GetGameLevels();
        for (int32 i = 0; i < Levels.Num(); i++)
        {
            USTULevelItemWidget* LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
            if (LevelItemWidget != nullptr)
            {
                LevelItemWidget->SetLevelData(i, Levels[i]);
                LevelItemWidget->LevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelItemSelected);
                LevelItemWidget->LevelFocused.AddUObject(this, &USTUMenuWidget::OnLevelItemFocused);
                LevelItemsBox->AddChild(LevelItemWidget);
                LevelItemWidgets.Add(LevelItemWidget);
            }
        }
    }
}

void USTUMenuWidget::OnLevelItemSelected(int32 Index)
{
    SelectedIndex = Index;

    for (int32 i = 0; i < LevelItemWidgets.Num(); i++)
    {
        const bool bIsSelected = SelectedIndex == i;
        LevelItemWidgets[i]->SetSelected(bIsSelected);
    }
}

void USTUMenuWidget::OnLevelItemFocused(int32 Index)
{
    for (int32 i = 0; i < LevelItemWidgets.Num(); i++)
    {
        const bool bIsFocused = Index == i;
        LevelItemWidgets[i]->SetFocused(bIsFocused);
    }
}

void USTUMenuWidget::LoadSelectedLevel()
{
    const USTUGameInstance* GameInstance = GetGameInstance<USTUGameInstance>();
    if (GameInstance != nullptr)
    {
        GameInstance->OpenGameLevel(SelectedIndex);
    }
}
