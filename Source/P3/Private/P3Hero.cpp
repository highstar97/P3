#include "P3Hero.h"
#include "P3HeroAnimInstance.h"
#include "P3GameInstance.h"
#include "P3StatComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

AP3Hero::AP3Hero()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Hero"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FClassFinder<UAnimInstance> HERO_ANIM(TEXT("/Game/Blueprints/HeroAnimBP.HeroAnimBP_C"));
	if (HERO_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(HERO_ANIM.Class);
	}

	SetCharacterType(ECharacterType::Hero);
}

void AP3Hero::InitStat()
{
	Super::InitStat();
	UP3GameInstance* P3GameInstance = Cast<UP3GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (P3GameInstance != nullptr)
	{
		FP3CharacterData* LevelBasedData = P3GameInstance->GetP3HeroData(1);
		GetStatComponent()->SetStatFromDataTable(1, LevelBasedData);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Hero] GameInstance is NULL."))
	}
}

void AP3Hero::Attack()
{
	Super::Attack();
	HeroAnim->PlayAttackMontage();
}

void AP3Hero::Die()
{
	Super::Die();
}

void AP3Hero::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	HeroAnim = Cast<UP3HeroAnimInstance>(GetMesh()->GetAnimInstance());
}
