#include "P3EnemyAnimInstance.h"
#include "P3Character.h"
#include "P3StateComponent.h"

UP3EnemyAnimInstance::UP3EnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_A(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Animations/PrimaryAttack_A_Slow_Montage_Golden_.PrimaryAttack_A_Slow_Montage_Golden_"));
	if (ATTACK_MONTAGE_A.Succeeded())
	{
		AttackMontage1 = ATTACK_MONTAGE_A.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_B(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Animations/PrimaryAttack_B_Slow_Montage_Golden_.PrimaryAttack_B_Slow_Montage_Golden_"));
	if (ATTACK_MONTAGE_B.Succeeded())
	{
		AttackMontage2 = ATTACK_MONTAGE_B.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_C(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Animations/PrimaryAttack_C_Slow_Montage_Golden_.PrimaryAttack_C_Slow_Montage_Golden_"));
	if (ATTACK_MONTAGE_C.Succeeded())
	{
		AttackMontage3 = ATTACK_MONTAGE_C.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_D(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/Animations/PrimaryAttack_D_Slow_Montage_Golden_.PrimaryAttack_D_Slow_Montage_Golden_"));
	if (ATTACK_MONTAGE_D.Succeeded())
	{
		AttackMontage4 = ATTACK_MONTAGE_D.Object;
	}
}

void UP3EnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UP3EnemyAnimInstance::PlayAttackMontage()
{
	if (P3Character->GetStateComponent()->GetbIsAttacking() == true) return;

	switch (P3Character->GetStateComponent()->GetAttackCount())
	{
	case 0:
	{
		Montage_Play(AttackMontage1, 1.0f);
		break;
	}
	case 1:
	{
		Montage_Play(AttackMontage2, 1.0f);
		break;
	}
	case 2:
	{
		Montage_Play(AttackMontage3, 1.0f);
		break;
	}
	case 3:
	{
		Montage_Play(AttackMontage4, 1.0f);
		break;
	}
	default:
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3EnemyAnimInstance] PlayAttackMontage's parameter Error."));
		break;
	}
	}
}