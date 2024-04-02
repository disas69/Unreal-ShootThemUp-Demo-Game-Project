// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STUHealthComponent.h"

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool USTUHealthComponent::AddHealth(float HealthAmount)
{
    if (!IsAlive() || Health >= MaxHealth)
    {
        return false;
    }

    SetHealth(Health + HealthAmount);
    return true;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner != nullptr)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnOwnerTakeDamage);
    }
}

void USTUHealthComponent::OnOwnerTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || !IsAlive())
    {
        return;
    }

    if (AutoHeal && HealTimerHandle.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }

    SetHealth(Health - Damage);

    if (IsAlive())
    {
        if (AutoHeal)
        {
            GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
        }
    }
    else
    {
        OnDeath.Broadcast();
    }
}

void USTUHealthComponent::HealUpdate()
{
    if (Health >= MaxHealth || !IsAlive())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
        return;
    }

    SetHealth(Health + HealAmount);
}

void USTUHealthComponent::SetHealth(const float NewHealth)
{
    const float PreviousHealth = Health;
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(PreviousHealth, Health);
}

