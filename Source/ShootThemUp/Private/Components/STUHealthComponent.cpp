// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STUHealthComponent.h"

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner != nullptr)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnOwnerTakeDamage);
    }
}

void USTUHealthComponent::OnOwnerTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || Health <= 0.0f || GetOwner() != DamagedActor)
    {
        return;
    }

    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
}
