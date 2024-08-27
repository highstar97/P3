#include "P3HeroAnimInstance.h"
#include "P3Character.h"
#include "P3StateComponent.h"

UP3HeroAnimInstance::UP3HeroAnimInstance()
{
	
}

void UP3HeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UP3HeroAnimInstance::PlayAttackMontage()
{
	if (P3Character->GetStateComponent()->GetbIsAttacking() == true) return;

	float AttackSpeed = 1.0f;	// if AttackSpeed == 2.0f -> double Attack in a second

	switch (P3Character->GetStateComponent()->GetAttackCount())
	{
	case 0:
	{
		if (!ensure(AttackMontage1 != nullptr)) return;
		Montage_Play(AttackMontage1, AttackSpeed);
		break;
	}
	case 1:
	{
		if (!ensure(AttackMontage2 != nullptr)) return;
		Montage_Play(AttackMontage2, AttackSpeed);
		break;
	}
	case 2:
	{
		if (!ensure(AttackMontage3 != nullptr)) return;
		Montage_Play(AttackMontage3, AttackSpeed);
		break;
	}
	case 3:
	{
		if (!ensure(AttackMontage4 != nullptr)) return;
		Montage_Play(AttackMontage4, AttackSpeed);
		break;
	}
	default:
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HeroAnimInstance] PlayAttackMontage's parameter Error."));
		break;
	}
	}
}

void UP3HeroAnimInstance::PlaySkillMontage(int32 SkillNumber)
{
	if (P3Character->GetStateComponent()->GetbIsUsingSkill() == true)
	{
		return;
	}

	switch (SkillNumber)
	{
	case 1:
	{
		if (!ensure(Skill1Montage != nullptr)) return;
		Montage_Play(Skill1Montage, 1.0f);
		break;
	}
	default:
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HeroAnimInstance] PlaySkillMontage's parameter Error."));
		break;
	}
	}
}