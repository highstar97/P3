#include "P3Weapon.h"

AP3Weapon::AP3Weapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComponent"));
	RootComponent = WeaponMeshComponent;
	WeaponMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void AP3Weapon::BeginPlay()
{
	Super::BeginPlay();	
}