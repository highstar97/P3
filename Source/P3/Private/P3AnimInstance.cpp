#include "P3AnimInstance.h"
#include "P3Character.h"
#include "P3StateComponent.h"

UP3AnimInstance::UP3AnimInstance()
{

}

void UP3AnimInstance::NativeInitializeAnimation()
{
	APawn* Pawn = TryGetPawnOwner();
	P3Character = Cast<AP3Character>(Pawn);

	if (P3Character == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3AnimInstance] P3Character is nullptr."));
	}
}

void UP3AnimInstance::PlayAttackMontage()
{
	
}

void UP3AnimInstance::AnimNotify_StartAttack()
{
	P3Character->GetStateComponent()->SetbIsAttacking(true);
}

void UP3AnimInstance::AnimNotify_SaveAttack()
{
	int PreAttackCount = P3Character->GetStateComponent()->GetAttackCount();
	if (PreAttackCount + 1 == NumOfAttackMontage)
	{
		P3Character->GetStateComponent()->SetAttackCount(0);
	}
	else
	{
		P3Character->GetStateComponent()->SetAttackCount(PreAttackCount + 1);
	}
}

void UP3AnimInstance::AnimNotify_EndAttack()
{
	P3Character->GetStateComponent()->SetbIsAttacking(false);
}

void UP3AnimInstance::AnimNotify_ResetCombo()
{
	P3Character->GetStateComponent()->SetAttackCount(0);
}