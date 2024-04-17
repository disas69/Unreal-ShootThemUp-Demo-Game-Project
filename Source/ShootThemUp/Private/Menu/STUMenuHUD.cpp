// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    USTUBaseWidget* MenuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidgetClass);
    if (MenuWidget != nullptr)
    {
        MenuWidget->AddToViewport();
        MenuWidget->Show();
    }
}