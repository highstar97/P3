#include "P3Heal.h"
#include "P3BuffComponent.h"

UP3Heal::UP3Heal()
{
	BuffType = EBuffType::Heal;
}

void UP3Heal::InitHeal(FString NewName, float NewDuration, float NewTotalHealAmount)
{
	Name = NewName;
	Duration = NewDuration;
	TotalHealAmount = NewTotalHealAmount;
}