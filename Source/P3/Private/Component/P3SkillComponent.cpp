#include "P3SkillComponent.h"
#include "P3GameInstance.h"
#include "Kismet/GameplayStatics.h"

UP3SkillComponent::UP3SkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bIsSkill1Cool = false;
	bIsSkill2Cool = false;
}

void UP3SkillComponent::BeginPlay()
{
	Super::BeginPlay();
}