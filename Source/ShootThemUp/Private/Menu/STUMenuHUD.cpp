// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Menu/STUMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTUMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    UUserWidget* MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
    if (MenuWidget != nullptr)
    {
        MenuWidget->AddToViewport();
    }
}