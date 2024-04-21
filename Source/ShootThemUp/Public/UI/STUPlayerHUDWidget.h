// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

class UImage;
class UProgressBar;
class USTUHealthComponent;
class USTUWeaponComponent;
class ASTUWeapon;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public USTUBaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetHealthText() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString GetAmmoText() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    ASTUWeapon* GetCurrentWeapon() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();
    
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float CriticalHealthThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor NormalColor = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor CriticalColor = FLinearColor::Red;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* DamageAnimation;

    UPROPERTY(meta = (BindWidget))
    UImage* DamageOverlay;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* HealAnimation;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    UFUNCTION()
    void OnHealthChanged(float NewHealth, float HealthDelta);
    void OnPossessNewPawn(APawn* Pawn);
    void UpdateHealthBar() const;
};
