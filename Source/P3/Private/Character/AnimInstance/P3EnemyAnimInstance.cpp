#include "P3EnemyAnimInstance.h"
#include "P3Character.h"
#include "P3StateComponent.h"

UP3EnemyAnimInstance::UP3EnemyAnimInstance()
{
	
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
		if (!ensure(AttackMontage1 != nullptr)) return;
		Montage_Play(AttackMontage1, 1.0f);
		break;
	}
	case 1:
	{
		if (!ensure(AttackMontage2 != nullptr)) return;
		Montage_Play(AttackMontage2, 1.0f);
		break;
	}
	case 2:
	{
		if (!ensure(AttackMontage3 != nullptr)) return;
		Montage_Play(AttackMontage3, 1.0f);
		break;
	}
	case 3:
	{
		if (!ensure(AttackMontage4 != nullptr)) return;
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