#include "P3Heal.h"
#include "P3BuffComponent.h"
#include "Particles/ParticleSystem.h"

UP3Heal::UP3Heal()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_HEAL(TEXT("/Game/InfinityBladeEffects/Effects/FX_Ability/Heal/P_Health_Pickup_01.P_Health_Pickup_01"));
	if (P_HEAL.Succeeded())
	{
		Particle = P_HEAL.Object;
	}

	BuffType = EBuffType::Heal;
}

void UP3Heal::InitHeal(FString NewName, float NewDuration, float NewTotalHealAmount)
{
	Name = NewName;
	Duration = NewDuration;
	TotalHealAmount = NewTotalHealAmount;
}