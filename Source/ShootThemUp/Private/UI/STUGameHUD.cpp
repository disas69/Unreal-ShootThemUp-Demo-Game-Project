// Shoot Them Up demo game project. Evgenii Esaulenko, 2024


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();
    DrawCrossHair();
}

FVector2D ASTUGameHUD::GetCrossHairPosition() const
{
    FVector2D ViewportSize;
    GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
    const FVector2D Center(ViewportSize.X * 0.5f, ViewportSize.Y * 0.5f);
    return Center + CrossHairOffset;
}

void ASTUGameHUD::DrawCrossHair()
{
    const FVector2D Center = GetCrossHairPosition();
    
    const float LineSize = 20.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::White;

    DrawLine(Center.X - LineSize / 2.0f, Center.Y, Center.X + LineSize / 2.0f, Center.Y, LineColor, LineThickness);
    DrawLine(Center.X, Center.Y - LineSize / 2.0f, Center.X, Center.Y + LineSize / 2.0f, LineColor, LineThickness);
}