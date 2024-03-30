// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUHealthComponent;
class USTUWeaponComponent;
class ASTUWeapon;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetAmmoText() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    ASTUWeapon* GetCurrentWeapon() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

private:
    USTUHealthComponent* GetHealthComponent() const;
    USTUWeaponComponent* GetWeaponComponent() const;
};
