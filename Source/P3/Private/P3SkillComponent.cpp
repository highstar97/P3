#include "P3SkillComponent.h"

UP3SkillComponent::UP3SkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bIsSkill1Cool = false;
}

FP3SkillData* UP3SkillComponent::GetSkill1DataFromTable(int32 FromLevel)
{
	if(Skill1DataTable == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3SkillComponent] Skill1DataTable is nullptr."));
		return nullptr;
	}
	return Skill1DataTable->FindRow<FP3SkillData>(*FString::FromInt(FromLevel), TEXT(""));
}

void UP3SkillComponent::SetSkill1DataFromLevel(int32 FromLevel)
{
	Skill1Data = GetSkill1DataFromTable(FromLevel);
}

void UP3SkillComponent::BeginPlay()
{
	Super::BeginPlay();
}