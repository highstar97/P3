#include "P3Hero.h"
#include "P3HeroController.h"
#include "P3HeroAnimInstance.h"
#include "P3GameInstance.h"
#include "P3ItemManager.h"
#include "P3StatComponent.h"
#include "P3StateComponent.h"
#include "P3SkillComponent.h"
#include "P3InventoryComponent.h"
#include "P3WeaponComponent.h"
#include "P3BuffComponent.h"
#include "P3Buff.h"
#include "P3Heal.h"
#include "P3Item.h"
#include "P3HUDWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	GetSkillComponent()->SetSkill1Name(FString::Printf(TEXT("Blink")));
	GetSkillComponent()->SetSkill2Name(FString::Printf(TEXT("Heal")));

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
		FP3CharacterData* LevelBasedStatData = P3GameInstance->GetP3HeroData(1);
		GetStatComponent()->SetStatFromDataTable(1, LevelBasedStatData);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Hero] GameInstance is NULL."))
	}
}

void AP3Hero::InitWeapon()
{
	Super::InitWeapon();
}

void AP3Hero::InitSkill()
{
	Super::InitSkill();
	UP3GameInstance* P3GameInstance = Cast<UP3GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (P3GameInstance != nullptr)
	{
		// Skill1
		FP3SkillData* LevelBasedSkill1Data = P3GameInstance->GetHeroSkill1Data(1);
		GetSkillComponent()->SetCurrentSkill1Data(LevelBasedSkill1Data);

		// Skill2
		FP3SkillData* LevelBasedSkill2Data = P3GameInstance->GetHeroSkill2Data(1);
		GetSkillComponent()->SetCurrentSkill2Data(LevelBasedSkill2Data);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Hero] GameInstance is NULL."))
	}
}

void AP3Hero::InitItem()
{
	Super::InitItem();
	UP3GameInstance* GameInstance = Cast<UP3GameInstance>(GetGameInstance());
	UP3ItemManager* ItemManager = GameInstance->GetItemManager();
	GetInventoryComponent()->AddItem(ItemManager->GetItemByKey(1), 3);
	GetInventoryComponent()->AddItem(ItemManager->GetItemByKey(2), 3);
}

void AP3Hero::Attack()
{
	Super::Attack();
	HeroAnim->PlayAttackMontage();
}

// Hero's Skill1 is Blink_Wind.
// Hides in the wind for a short time(1.0 sec) and reappears from the front.
void AP3Hero::Skill1()
{
	Super::Skill1();

	// IsSkill1Cool?
	if (GetSkillComponent()->GetbIsSkill1Cool() == true)
	{
		// CoolTime
		return;
	}

	// Consume Mana
	if (ConsumeMP(GetSkillComponent()->GetSkill1NeededMP()) == false)
	{
		// Not Enough Mana
		return;
	}
	
	AP3HeroController* HeroController = Cast<AP3HeroController>(Controller);
	if (HeroController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Hero] : Can't Access to Controller."));
	}
	{
		// DisableButtonSkill1 in HUD.
		HeroController->GetHUDWidget()->SetEnableButtonSkill1(false);

		// Start HUD Skill1 CoolTime UpdateTimer
		HeroController->GetHUDWidget()->StartUpdateButtonSkill1(GetSkillComponent()->GetSkill1CoolTime());
	}

	// CoolTime;
	GetSkillComponent()->SetbIsSkill1Cool(true);
	FTimerHandle CoolTimerHandle = {};
	GetWorld()->GetTimerManager().SetTimer(CoolTimerHandle, FTimerDelegate::CreateLambda([this, HeroController]() -> void {
		GetSkillComponent()->SetbIsSkill1Cool(false);
		HeroController->GetHUDWidget()->SetEnableButtonSkill1(true);
		}), GetSkillComponent()->GetSkill1CoolTime(), false);

	// Skill1 
	float DistanceToMove = 1000.0f;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + GetControlRotation().Vector() * DistanceToMove;
	FVector FinalLocation;

	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);		// I don't know why bIgnoreselr is not work...

	bool Result = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		StartLocation,
		EndLocation,
		UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel4),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		3.0f
	);

	if (Result == true)
	{
		FinalLocation = HitResult.ImpactPoint - GetActorForwardVector() * -55.0f;	// Capsule's radius is 45.0f

		FString ErrorMeshName = "ElvenRuins_Terrain3_4";							// Becuase of Map, Sometimes character go underground.
		if (HitResult.GetActor()->GetName() == ErrorMeshName)
		{
			FinalLocation.Z += 200.0f;
		}
		FString ss = HitResult.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("[P3Hero] Character use Skill1(Dash) and Block on %s."), *ss);
	}
	else
	{
		FinalLocation = HitResult.TraceEnd;
	}

	GetMesh()->SetHiddenInGame(true);
	GetWeaponComponent()->HideWeapon(true);

	HeroAnim->PlaySkillMontage(1);

	SetActorRelativeLocation(FinalLocation);

	FTimerHandle HideTimerHandle = {};
	GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
		GetMesh()->SetHiddenInGame(false);
		GetWeaponComponent()->HideWeapon(false);
		}), 0.3f, false);
}

// Hero's Skill2 is Buff.
void AP3Hero::Skill2()
{
	Super::Skill2();

	// IsSkill2Cool?
	if (GetSkillComponent()->GetbIsSkill2Cool() == true)
	{
		// CoolTime
		return;
	}

	// Consume Mana
	if (ConsumeMP(GetSkillComponent()->GetSkill2NeededMP()) == false)
	{
		// Not Enough Mana
		return;
	}

	AP3HeroController* HeroController = Cast<AP3HeroController>(Controller);
	if (HeroController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Hero] : Can't Access to Controller."));
	}
	else
	{
		// DisableButtonSkill2 in HUD.
		HeroController->GetHUDWidget()->SetEnableButtonSkill2(false);

		// Start HUD Skill2 CoolTime UpdateTimer
		HeroController->GetHUDWidget()->StartUpdateButtonSkill2(GetSkillComponent()->GetSkill2CoolTime());
	}

	// CoolTime;
	GetSkillComponent()->SetbIsSkill2Cool(true);
	FTimerHandle CoolTimerHandle = {};
	GetWorld()->GetTimerManager().SetTimer(CoolTimerHandle, FTimerDelegate::CreateLambda([this, HeroController]() -> void {
		GetSkillComponent()->SetbIsSkill2Cool(false);
		HeroController->GetHUDWidget()->SetEnableButtonSkill2(true);
		}), GetSkillComponent()->GetSkill2CoolTime(), false);

	// Skill2
	UP3Heal* BuffHeal = NewObject<UP3Heal>();
	BuffHeal->InitHeal(FString::Printf(TEXT("Skill2's Heal")), 10.0f, 200.0f);
	GetBuffComponent()->ApplyBuff(BuffHeal);
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
