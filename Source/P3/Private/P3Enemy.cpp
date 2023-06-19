#include "P3Enemy.h"
#include "Components/CapsuleComponent.h"

AP3Enemy::AP3Enemy()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	SetCharacterType(ECharacterType::Enemy);
}

void AP3Enemy::Attack()
{
	Super::Attack();
}

void AP3Enemy::Die()
{
	Super::Die();
}

void AP3Enemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}