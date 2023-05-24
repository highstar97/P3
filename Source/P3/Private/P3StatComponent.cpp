#include "P3StatComponent.h"
#include "P3GameInstance.h"

void UP3StatComponent::SetStatFromDataTable(int32 _Level, FP3CharacterData* Data)
{
	this->Level = _Level;
	this->MaxHP = Data->MaxHP;
	this->CurrentHP = this->MaxHP;
	this->MaxMP = Data->MaxMP;
	this->CurrentMP = this->MaxMP;
	this->CurrentExp = 0;
	this->RequiredExp = Data->RequiredExp;
}

void UP3StatComponent::BeginPlay()
{
	Super::BeginPlay();
}