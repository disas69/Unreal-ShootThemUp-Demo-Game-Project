// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUButtonWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USTUButtonWidget::SetFocus(bool bFocus)
{
    if (bFocus)
    {
        Button->SetKeyboardFocus();
    }
}

void USTUButtonWidget::NativeConstruct()
{
    Super::NativeConstruct();
    TextBlock->SetText(Text);
    Button->SetColorAndOpacity(DefaultColor);
}

void USTUButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (Button->HasKeyboardFocus())
    {
        Button->SetColorAndOpacity(FocusedColor);
    }
    else
    {
        Button->SetColorAndOpacity(DefaultColor);
    }
}
