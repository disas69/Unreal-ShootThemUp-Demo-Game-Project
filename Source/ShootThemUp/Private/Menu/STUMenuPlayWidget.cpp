// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuPlayWidget.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/STULevelItemWidget.h"
#include "Menu/STUMenuWidget.h"
#include "Sound/SoundCue.h"

bool USTUMenuPlayWidget::Initialize()
{
    const bool bResult = Super::Initialize();

    if (StartGameButton != nullptr)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuPlayWidget::StartGame);
    }

    if (BackButton != nullptr)
    {
        BackButton->OnClicked.AddDynamic(this, &USTUMenuPlayWidget::OpenMenu);
    }

    CreateLevelItems();

    if (LevelItemWidgets.Num() > 0)
    {
        OnLevelItemSelected(0);
        OnLevelItemFocused(0);
    }

    return bResult;
}

void USTUMenuPlayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // GetWorld()->GetTimerManager().SetTimerForNextTick(
    //     [&]
    //     {
    //         if (LevelItemWidgets.Num() > 0)
    //         {
    //             OnLevelItemFocused(0);
    //         }
    //
    //         StartGameButton->IsFocusable = true;
    //         StartGameButton->SetKeyboardFocus();
    //     });
}

void USTUMenuPlayWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);

    if (Animation == LoadingAnimation)
    {
        LoadSelectedLevel();
    }
}

void USTUMenuPlayWidget::CreateLevelItems()
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
                LevelItemWidget->LevelSelected.AddUObject(this, &USTUMenuPlayWidget::OnLevelItemSelected);
                LevelItemWidget->LevelFocused.AddUObject(this, &USTUMenuPlayWidget::OnLevelItemFocused);
                LevelItemsBox->AddChild(LevelItemWidget);
                LevelItemWidgets.Add(LevelItemWidget);
            }
        }
    }
}

void USTUMenuPlayWidget::OnLevelItemSelected(int32 Index)
{
    SelectedIndex = Index;

    for (int32 i = 0; i < LevelItemWidgets.Num(); i++)
    {
        const bool bIsSelected = SelectedIndex == i;
        LevelItemWidgets[i]->SetSelected(bIsSelected);
    }
}

void USTUMenuPlayWidget::OnLevelItemFocused(int32 Index)
{
    for (int32 i = 0; i < LevelItemWidgets.Num(); i++)
    {
        const bool bIsFocused = Index == i;
        LevelItemWidgets[i]->SetFocused(bIsFocused);
    }
}

void USTUMenuPlayWidget::LoadSelectedLevel()
{
    const USTUGameInstance* GameInstance = GetGameInstance<USTUGameInstance>();
    if (GameInstance != nullptr)
    {
        GameInstance->OpenGameLevel(SelectedIndex);
    }
}

void USTUMenuPlayWidget::StartGame()
{
    if (IsAnimationPlaying(LoadingAnimation))
    {
        return;
    }

    PlayAnimation(LoadingAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void USTUMenuPlayWidget::OpenMenu()
{
    USTUMenuWidget* MenuWidget = CreateWidget<USTUMenuWidget>(GetWorld(), MenuWidgetClass);
    if (MenuWidget != nullptr)
    {
        MenuWidget->AddToViewport();
        MenuWidget->Show(false);
        RemoveFromParent();
    }
}