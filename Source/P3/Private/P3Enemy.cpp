#include "P3Enemy.h"
#include "P3EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AP3Enemy::AP3Enemy()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENEMY_ANIM(TEXT("/Game/Blueprints/EnemyAnimBP.EnemyAnimBP_C"));
	if (ENEMY_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ENEMY_ANIM.Class);
	}

	SetCharacterType(ECharacterType::Enemy);
}

void AP3Enemy::Attack()
{
	Super::Attack();
	EnemyAnim->PlayAttackMontage();
}

void AP3Enemy::Die()
{
	Super::Die();
}

void AP3Enemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	EnemyAnim = Cast<UP3EnemyAnimInstance>(GetMesh()->GetAnimInstance());
}