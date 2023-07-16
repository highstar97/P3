#include "P3StatComponent.h"
#include "P3GameInstance.h"


void UP3StatComponent::LevelUp()
{
	if (LevelBasedCurrentData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3StatComponent] LevelBasedCurrentData is NULL."));
		return;
	}

	// When the level is updated, HP and MP are filled to Max. CurrentExp is not affected by LevelUp().
	SetMaxHP(LevelBasedCurrentData->MaxHP);
	SetCurrentHP(this->MaxHP);
	SetMaxMP(LevelBasedCurrentData->MaxMP);
	SetCurrentMP(this->MaxMP);
	SetAttack(LevelBasedCurrentData->Attack);
	SetRequiredExp(LevelBasedCurrentData->RequiredExp);

	OnHPChanged.Broadcast();
	OnMPChanged.Broadcast();
	OnExpChanged.Broadcast();
}

void UP3StatComponent::ConsumeMP(float UsedMP)
{
	CurrentMP -= UsedMP;
	OnMPChanged.Broadcast();
}

void UP3StatComponent::AddExp(float GainedExp)
{
	CurrentExp += GainedExp;
	if (CurrentExp >= RequiredExp)
	{
		CurrentExp -= RequiredExp;
		OnLevelUp.Broadcast();
	}
	OnExpChanged.Broadcast();
}

void UP3StatComponent::SetStatFromDataTable(int32 NewLevel, FP3CharacterData* LevelBasedData)
{
	SetLevel(NewLevel);
	SetLevelBasedCurrentData(LevelBasedData);
	LevelUp();
}

void UP3StatComponent::SetCurrentHP(float NewCurrentHP)
{
	this->CurrentHP = NewCurrentHP;

	OnHPChanged.Broadcast();

	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UP3StatComponent::TakeDamage(float TakenDamage)
{
	// Damage logic : Damage = Attack (when defense stat update? will changed?)
	float Damage = TakenDamage;
	
	SetCurrentHP(FMath::Clamp(GetCurrentHP() - Damage,0.0f,GetMaxHP()));

	return Damage;
}

void UP3StatComponent::BeginPlay()
{
	Super::BeginPlay();
}