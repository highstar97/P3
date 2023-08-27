#include "P3Weapon.h"

AP3Weapon::AP3Weapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	RootComponent = WeaponMeshComponent;
	Radius = 0.0f;
}

void AP3Weapon::BeginPlay()
{
	Super::BeginPlay();	
}