#include "P3HeroAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UP3HeroAnimInstance::UP3HeroAnimInstance()
{
	IsAttacking = false;
	IsInAir = false;
	IsAccelerating = false;
	AttackCount = 0;
	Speed = 0.0f;
	Pitch = 0.0f;
	Yaw = 0.0f;
	Roll = 0.0f;
	YawDelta = 0.0f;
	RotationLastTick = FRotator::ZeroRotator;

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

void UP3HeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		IsInAir = Pawn->GetMovementComponent()->IsFalling();
		IsAccelerating = Cast<ACharacter>(Pawn)->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.0f ? true : false;
		Speed = Pawn->GetVelocity().Length();
		FRotator DeltaRotator = (Pawn->GetBaseAimRotation() - Pawn->GetActorRotation());
		Pitch = DeltaRotator.Pitch;
		Yaw = DeltaRotator.Yaw;
		Roll = DeltaRotator.Roll;
		RotationLastTick = Pawn->GetActorRotation();
		YawDelta = FMath::FInterpTo(YawDelta, (((RotationLastTick - Pawn->GetActorRotation()).Yaw / DeltaSeconds) / 7.0f), DeltaSeconds, 6.0f);
	}
}

void UP3HeroAnimInstance::PlayAttackMontage()
{
	if (IsAttacking) return;

	switch (AttackCount)
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
	IsAttacking = true;
}

void UP3HeroAnimInstance::AnimNotify_SaveAttack()
{
	if (++AttackCount > 4)
	{
		AttackCount = 0;
	}
}

void UP3HeroAnimInstance::AnimNotify_EndAttack()
{
	IsAttacking = false;
}

void UP3HeroAnimInstance::AnimNotify_ResetCombo()
{
	AttackCount = 0;
}
