// Shoot Them Up demo game project. Evgenii Esaulenko, 2024


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();
    DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair()
{
    const FVector2D Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float LineSize = 20.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::White;

    DrawLine(Center.X - LineSize / 2.0f, Center.Y, Center.X + LineSize / 2.0f, Center.Y, LineColor, LineThickness);
    DrawLine(Center.X, Center.Y - LineSize / 2.0f, Center.X, Center.Y + LineSize / 2.0f, LineColor, LineThickness);
}