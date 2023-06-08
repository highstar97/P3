#include "P3HeroAnimInstance.h"
#include "P3Character.h"
#include "P3StateComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}

void UP3HeroAnimInstance::NativeInitializeAnimation()
{
	APawn* Pawn = TryGetPawnOwner();
	P3Character = Cast<AP3Character>(Pawn);
	
	if (P3Character == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HeroAnimInstance] P3Character is nullptr."));
	}
}

void UP3HeroAnimInstance::PlayAttackMontage()
{
	if (P3Character->GetStateComponent()->GetIsAttacking() == true) return;

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
		UE_LOG(LogTemp, Warning, TEXT("[P3HeroAnimInstance] PlayAttackMontage's parameter Error."));
		break;
	}
	}
}

void UP3HeroAnimInstance::AnimNotify_StartAttack()
{
	P3Character->GetStateComponent()->SetIsAttacking(true);
}

void UP3HeroAnimInstance::AnimNotify_SaveAttack()
{
	int PreAttackCount = P3Character->GetStateComponent()->GetAttackCount();
	if (PreAttackCount+1 == NumOfAttackMontage)
	{
		P3Character->GetStateComponent()->SetAttackCount(0);
	}
	else
	{
		P3Character->GetStateComponent()->SetAttackCount(PreAttackCount + 1);
	}
}

void UP3HeroAnimInstance::AnimNotify_EndAttack()
{
	P3Character->GetStateComponent()->SetIsAttacking(false);
}

void UP3HeroAnimInstance::AnimNotify_ResetCombo()
{
	P3Character->GetStateComponent()->SetAttackCount(0);
}
