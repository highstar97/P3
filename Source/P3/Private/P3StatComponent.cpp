#include "P3StatComponent.h"
#include "P3GameInstance.h"

void UP3StatComponent::SetStatFromDataTable(int32 _Level, FP3CharacterData* LevelBasedData)
{
	if (LevelBasedCurrentStat == nullptr)
	{
		LevelBasedCurrentStat = LevelBasedData;
	}

	SetLevel(_Level);
}

void UP3StatComponent::SetLevel(int32 _Level)
{
	if (LevelBasedCurrentStat == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3StatComponent] LevelBasedCurrentStat is NULL."));
		return;
	}

	// When the level is updated, HP and MP are filled to Max.
	this->Level = _Level;
	SetMaxHP(LevelBasedCurrentStat->MaxHP);
	SetCurrentHP(this->MaxHP);
	SetMaxMP(LevelBasedCurrentStat->MaxMP);
	SetCurrentMP(this->MaxMP);
	SetRequiredExp(LevelBasedCurrentStat->RequiredExp);
	SetCurrentExp(0);
	
	OnHPChanged.Broadcast();
}

void UP3StatComponent::BeginPlay()
{
	Super::BeginPlay();
}