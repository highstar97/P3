#include "P3HPRegen.h"
#include "P3BuffComponent.h"
#include "Particles/ParticleSystem.h"

UP3HPRegen::UP3HPRegen()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE_HPRegen(TEXT("/Game/GameData/Images/Image_Heal.Image_Heal"));
	if (IMAGE_HPRegen.Succeeded())
	{
		Image = IMAGE_HPRegen.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_HPRegen(TEXT("/Game/InfinityBladeEffects/Effects/FX_Ability/Heal/P_Health_Pickup_01.P_Health_Pickup_01"));
	if (P_HPRegen.Succeeded())
	{
		Particle = P_HPRegen.Object;
	}

	BuffType = EBuffType::HPREGEN;
}

void UP3HPRegen::InitBuffData(FString NewName, float NewDuration, float NewTotalAmount)
{
	Name = NewName;
	Duration = NewDuration;
	TotalAmount = NewTotalAmount;
}