#include "P3HeroAnimInstance.h"
#include "P3Character.h"
#include "P3StateComponent.h"

UP3HeroAnimInstance::UP3HeroAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_A(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_A_Slow_Montage.PrimaryAttack_A_Slow_Montage"));
	if (ATTACK_MONTAGE_A.Succeeded())
	{
		AttackMontage1 = ATTACK_MONTAGE_A.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_B(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_B_Slow_Montage.PrimaryAttack_B_Slow_Montage"));
	if (ATTACK_MONTAGE_B.Succeeded())
	{
		AttackMontage2 = ATTACK_MONTAGE_B.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_C(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_C_Slow_Montage.PrimaryAttack_C_Slow_Montage"));
	if (ATTACK_MONTAGE_C.Succeeded())
	{
		AttackMontage3 = ATTACK_MONTAGE_C.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_D(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/PrimaryAttack_D_Slow_Montage.PrimaryAttack_D_Slow_Montage"));
	if (ATTACK_MONTAGE_D.Succeeded())
	{
		AttackMontage4 = ATTACK_MONTAGE_D.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_MONTAGE_1(TEXT("/Game/ParagonKwang/Characters/Heroes/Kwang/Animations/Skill_Blink_Wind.Skill_Blink_Wind"));
	if (SKILL_MONTAGE_1.Succeeded())
	{
		Skill1Montage = SKILL_MONTAGE_1.Object;
	}
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
		Montage_Play(AttackMontage1, AttackSpeed);
		break;
	}
	case 1:
	{
		Montage_Play(AttackMontage2, AttackSpeed);
		break;
	}
	case 2:
	{
		Montage_Play(AttackMontage3, AttackSpeed);
		break;
	}
	case 3:
	{
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