#include "P3Enemy.h"
#include "P3EnemyAnimInstance.h"
#include "P3GameInstance.h"
#include "P3ItemManager.h"
#include "P3StatComponent.h"
#include "P3InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

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

void AP3Enemy::InitStat()
{
	Super::InitStat();
	UP3GameInstance* P3GameInstance = Cast<UP3GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (P3GameInstance != nullptr)
	{
		FP3CharacterData* LevelBasedData = P3GameInstance->GetP3EnemyData(1);
		GetStatComponent()->SetStatFromDataTable(1, LevelBasedData);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Enemy] GameInstance is NULL."))
	}
}

void AP3Enemy::InitWeapon()
{
	Super::InitWeapon();
}

void AP3Enemy::InitSkill()
{
	Super::InitSkill();
}

void AP3Enemy::InitItem()
{
	Super::InitItem();
	UP3GameInstance* GameInstance = Cast<UP3GameInstance>(GetGameInstance());
	UP3ItemManager* ItemManager = GameInstance->GetItemManager();
	GetInventoryComponent()->AddItem(ItemManager->GetItemByKey(1), 10);
	GetInventoryComponent()->AddItem(ItemManager->GetItemByKey(2), 10);
}

void AP3Enemy::Attack()
{
	Super::Attack();
	EnemyAnim->PlayAttackMontage();
}

void AP3Enemy::Skill1()
{
	Super::Skill1();
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