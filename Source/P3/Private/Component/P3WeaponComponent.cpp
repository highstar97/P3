#include "P3WeaponComponent.h"
#include "P3Character.h"
#include "P3Weapon.h"
#include "P3BasicSword.h"

UP3WeaponComponent::UP3WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

AP3Weapon* UP3WeaponComponent::SpawnBasicSword()
{
	AP3Weapon* BasicSword = GetWorld()->SpawnActor<AP3BasicSword>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (BasicSword == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3WeaponComponent] Can't Spawn BasicSword."));
		return nullptr;
	}
	return BasicSword;
}

void UP3WeaponComponent::EquipWeapon(AP3Weapon* NewWeapon)
{
	Weapon = NewWeapon;
	FName WeaponSocket(TEXT("WeaponSocket"));
	AP3Character* Character = Cast<AP3Character>(GetOwner());
	Weapon->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
}

void UP3WeaponComponent::HideWeapon(bool NewHidden)
{
	Weapon->GetWeaponMeshComponent()->SetHiddenInGame(NewHidden);
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