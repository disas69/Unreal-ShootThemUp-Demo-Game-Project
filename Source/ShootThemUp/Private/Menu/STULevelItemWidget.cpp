// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STULevelItemWidget.h"
#include "FSTUTextUtils.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

bool USTULevelItemWidget::Initialize()
{
    const bool bResult = Super::Initialize();
    if (SelectLevelButton != nullptr)
    {
        SelectLevelButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::SelectLevel);
        SelectLevelButton->OnHovered.AddDynamic(this, &USTULevelItemWidget::FocusLevel);
    }

    return bResult;
}

void USTULevelItemWidget::SetLevelData(int32 Index, const FLevelData& Data)
{
    LevelIndex = Index;
    LevelName->SetText(FSTUTextUtils::TextFromString(Data.Name));
    LevelPreview->SetBrushFromTexture(Data.Preview);
}

void USTULevelItemWidget::SetSelected(bool bIsSelected) const
{
    LevelPreview->SetColorAndOpacity(bIsSelected ? FLinearColor::Red : FLinearColor::White);
}

void USTULevelItemWidget::SetFocused(bool bIsFocused) const
{
    Frame->SetVisibility(bIsFocused ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTULevelItemWidget::SelectLevel()
{
    LevelSelected.Broadcast(LevelIndex);
}

void USTULevelItemWidget::FocusLevel()
{
    LevelFocused.Broadcast(LevelIndex);
}