#include "P3BasicSword.h"

AP3BasicSword::AP3BasicSword()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BASICSWORD(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_HeroSword10/SK_Blade_HeroSword10.SK_Blade_HeroSword10"));
	if (SK_BASICSWORD.Succeeded())
	{
		WeaponMeshComponent->SetSkeletalMesh(SK_BASICSWORD.Object);
	}
	Radius = 20.0f;
}