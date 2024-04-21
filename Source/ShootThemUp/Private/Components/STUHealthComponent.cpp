// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Components/STUHealthComponent.h"
#include "STUGameModeBase.h"
#include "GameFramework/Character.h"
#include "Perception/AISenseEvent_Damage.h"

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
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnOwnerTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnOwnerTakeRadialDamage);
    }
}

void USTUHealthComponent::OnOwnerTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
    const float DamageModifier = GetPointDamageModifier(DamagedActor, BoneName);
    Damage *= DamageModifier;
    
    ApplyDamage(DamagedActor, Damage, InstigatedBy);
}

void USTUHealthComponent::OnOwnerTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    ApplyDamage(DamagedActor, Damage, InstigatedBy);
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
    OnHealthChanged.Broadcast(Health, Health - PreviousHealth);
}

void USTUHealthComponent::ReportDamageEvent(AActor* DamagedActor, const AController* Instigator, float DamageAmount) const
{
    if (Instigator == nullptr || Instigator->GetPawn() == nullptr)
    {
        return;
    }

    UAISense_Damage::ReportDamageEvent(GetWorld(), DamagedActor, Instigator->GetPawn(), DamageAmount, Instigator->GetPawn()->GetActorLocation(), DamagedActor->GetActorLocation());
    OnDamageApplied.Broadcast(DamagedActor, DamageAmount, Instigator);
}

void USTUHealthComponent::ReportDeathEvent(AController* Killed, const AController* Killer) const
{
    ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode != nullptr)
    {
        GameMode->OnPlayerKilled(Killed, Killer);
    }

    OnDeath.Broadcast();
}

void USTUHealthComponent::ApplyDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy)
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
    ReportDamageEvent(DamagedActor, InstigatedBy, Damage);

    if (IsAlive())
    {
        if (AutoHeal)
        {
            GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
        }
    }
    else
    {
        ReportDeathEvent(DamagedActor->GetInstigatorController(), InstigatedBy);
    }
}

float USTUHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
    if (DamageModifiers.Num() == 0)
    {
        return 1.0f;
    }

    const ACharacter* DamagedCharacter = Cast<ACharacter>(DamagedActor);
    if (DamagedCharacter != nullptr)
    {
        const UPhysicalMaterial* PhysicalMaterial = DamagedCharacter->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
        if (PhysicalMaterial != nullptr)
        {
            if (DamageModifiers.Contains(PhysicalMaterial))
            {
                return DamageModifiers[PhysicalMaterial];
            }
        }
    }

    return 1.0f;
}
