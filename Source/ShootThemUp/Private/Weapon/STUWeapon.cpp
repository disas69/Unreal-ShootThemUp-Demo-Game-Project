// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "Weapon/STUWeapon.h"

ASTUWeapon::ASTUWeapon()
{
    PrimaryActorTick.bCanEverTick = false;
    
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUWeapon::BeginPlay()
{
    Super::BeginPlay();
}
