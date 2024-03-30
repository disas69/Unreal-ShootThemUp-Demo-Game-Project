// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const APawn* PlayerPawn = GetOwningPlayerPawn();
    if (PlayerPawn != nullptr)
    {
        const USTUHealthComponent* HealthComponent = PlayerPawn->FindComponentByClass<USTUHealthComponent>();
        if (HealthComponent != nullptr)
        {
            return HealthComponent->GetHealthPercent();
        }
    }

    return 0.0f;
}