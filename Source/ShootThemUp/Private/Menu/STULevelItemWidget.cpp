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
    Frame->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTULevelItemWidget::SelectLevel()
{
    LevelSelected.Broadcast(LevelIndex);
}