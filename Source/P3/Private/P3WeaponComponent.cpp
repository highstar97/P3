#include "P3WeaponComponent.h"
#include "P3Character.h"
#include "P3Weapon.h"

UP3WeaponComponent::UP3WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<AP3Weapon> BP_BASIC_SWORD(TEXT("/Game/Blueprints/Weapon_BasicSword.Weapon_BasicSword_C"));
	if (BP_BASIC_SWORD.Succeeded())
	{
		WeaponClass = BP_BASIC_SWORD.Class;
	}
}

AP3Weapon* UP3WeaponComponent::SpawnBasicSword()
{
	AP3Weapon* SpawnedWeapon = GetWorld()->SpawnActor<AP3Weapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
	return SpawnedWeapon;
}

void UP3WeaponComponent::EquipWeapon(AP3Weapon* NewWeapon)
{
	Weapon = NewWeapon;
	FName WeaponSocket(TEXT("WeaponSocket"));
	AP3Character* Character = Cast<AP3Character>(GetOwner());
	Weapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
}

void UP3WeaponComponent::DestroyWeapon()
{
	Weapon->Destroy();
}

float UP3WeaponComponent::GetWeaponRadius() const
{
	if (Weapon != nullptr)
	{
		return Weapon->GetRaidus();
	}
	return 0.0f;
}

void UP3WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}