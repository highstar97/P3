#include "P3Hero.h"
#include "P3HeroAnimInstance.h"
#include "Components/CapsuleComponent.h"

AP3Hero::AP3Hero()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Hero"));

	static ConstructorHelpers::FClassFinder<UAnimInstance> HERO_ANIM(TEXT("/Game/Blueprints/HeroAnimBP.HeroAnimBP_C"));
	if (HERO_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(HERO_ANIM.Class);
	}

	SetCharacterType(ECharacterType::Hero);
}

void AP3Hero::Attack()
{
	Super::Attack();
	HeroAnim->PlayAttackMontage();
}

void AP3Hero::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	HeroAnim = Cast<UP3HeroAnimInstance>(GetMesh()->GetAnimInstance());
}
