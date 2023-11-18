#include "P3Character.h"
#include "P3HeroController.h"
#include "P3StatComponent.h"
#include "P3StateComponent.h"
#include "P3SkillComponent.h"
#include "P3WeaponComponent.h"
#include "P3BuffComponent.h"
#include "P3InventoryComponent.h"
#include "P3GameInstance.h"
#include "P3HUDWidget.h"
#include "P3InventoryWidget.h"
#include "P3HPBarWidget.h"
#include "P3DamageNumberWidget.h"
#include "P3Weapon.h"
#include "P3Item.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

AP3Character::AP3Character()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 700.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	StatComponent = CreateDefaultSubobject<UP3StatComponent>(TEXT("StatComponent"));
	StateComponent = CreateDefaultSubobject<UP3StateComponent>(TEXT("StateComponent"));
	SkillComponent = CreateDefaultSubobject<UP3SkillComponent>(TEXT("SkillComponent"));
	WeaponComponent = CreateDefaultSubobject<UP3WeaponComponent>(TEXT("WeaponComponent"));
	BuffComponent = CreateDefaultSubobject<UP3BuffComponent>(TEXT("BuffComponent"));
	InventoryComponent = CreateDefaultSubobject<UP3InventoryComponent>(TEXT("InventoryComponent"));

	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HPBarWidgetComponent->SetupAttachment(RootComponent);
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	static ConstructorHelpers::FClassFinder<UP3HPBarWidget> UI_HPBAR(TEXT("/Game/Blueprints/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HPBAR.Succeeded())
	{
		HPBarWidgetComponent->SetWidgetClass(UI_HPBAR.Class);
		HPBarWidgetComponent->SetDrawSize(FVector2D(100.0f, 30.0f));
	}

	static ConstructorHelpers::FClassFinder<UP3DamageNumberWidget> UI_DAMAGENUMBER(TEXT("/Game/Blueprints/UI/UI_DamageNumber.UI_DamageNumber_C"));
	if (UI_DAMAGENUMBER.Succeeded())
	{
		DamageNumberWidgetClass = UI_DAMAGENUMBER.Class;
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT(TEXT("/Game/Input/IMC_Default.IMC_Default"));
	if (IMC_DEFAULT.Succeeded())
	{
		DefaultMappingContext = IMC_DEFAULT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMP(TEXT("/Game/Input/Actions/IA_Jump.IA_Jump"));
	if (IA_JUMP.Succeeded())
	{
		JumpAction = IA_JUMP.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVE(TEXT("/Game/Input/Actions/IA_Move.IA_Move"));
	if (IA_MOVE.Succeeded())
	{
		MoveAction = IA_MOVE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOK(TEXT("/Game/Input/Actions/IA_Look.IA_Look"));
	if (IA_LOOK.Succeeded())
	{
		LookAction = IA_LOOK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ATTACK(TEXT("/Game/Input/Actions/IA_Attack.IA_Attack"));
	if (IA_ATTACK.Succeeded())
	{
		AttackAction= IA_ATTACK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SKILL1(TEXT("/Game/Input/Actions/IA_Skill1.IA_Skill1"));
	if (IA_SKILL1.Succeeded())
	{
		Skill1Action = IA_SKILL1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_SKILL2(TEXT("/Game/Input/Actions/IA_Skill2.IA_Skill2"));
	if (IA_SKILL2.Succeeded())
	{
		Skill2Action = IA_SKILL2.Object;
	}

	SetCharacterType(ECharacterType::None);
}

void AP3Character::BeginPlay()
{
	Super::BeginPlay();
	if (AP3HeroController* HeroController = Cast<AP3HeroController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(HeroController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		HeroController->GetHUDWidget()->BindCharacterStat(GetStatComponent());
		HeroController->GetHUDWidget()->BindCharacterBuff(GetBuffComponent());
		HeroController->GetInventoryWidget()->BindInventory(GetInventoryComponent());
	}

	UP3HPBarWidget* HPBarWidget = Cast<UP3HPBarWidget>(HPBarWidgetComponent->GetUserWidgetObject());
	if (HPBarWidget != nullptr)
	{
		HPBarWidget->BindCharacterStat(GetStatComponent());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Character] HPBarWidget is NULL."));
	}
	
	InitStat();
	InitWeapon();
	InitSkill();
	InitItem();
}

void AP3Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AP3Character::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AP3Character::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AP3Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AP3Character::Look);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AP3Character::Attack);
		EnhancedInputComponent->BindAction(Skill1Action, ETriggerEvent::Triggered, this, &AP3Character::Skill1);
		EnhancedInputComponent->BindAction(Skill2Action, ETriggerEvent::Triggered, this, &AP3Character::Skill2);
	}
}

void AP3Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetStatComponent()->OnHPIsZero.AddUObject(this, &AP3Character::Die);
	GetStatComponent()->OnLevelUp.AddUObject(this, &AP3Character::LevelUp);
	
	GetBuffComponent()->OnHealBuffStarted.AddUObject(this, &AP3Character::Heal);
	GetBuffComponent()->OnManaRegenBuffStarted.AddUObject(this, &AP3Character::ManaRegen);
}

void AP3Character::Jump()
{
	GetStateComponent()->SetbIsInAir(true);
	Super::Jump();
}

void AP3Character::StopJumping()
{
	GetStateComponent()->SetbIsInAir(false);
	Super::StopJumping();
}

void AP3Character::InitStat()
{
	
}

void AP3Character::InitWeapon()
{
	AP3Weapon* BasicSword = GetWeaponComponent()->SpawnBasicSword();
	if (BasicSword != nullptr)
	{
		GetWeaponComponent()->EquipWeapon(BasicSword);
	}
}

void AP3Character::InitSkill()
{

}

void AP3Character::InitItem()
{

}

void AP3Character::Attack()
{
	
}

void AP3Character::Skill1()
{
	
}

void AP3Character::Skill2()
{

}

void AP3Character::Die()
{
	FTimerHandle DeadTimerHandle = {};
	GetStateComponent()->SetbIsDead(true);
	SetActorEnableCollision(false);
	HPBarWidgetComponent->SetHiddenInGame(true);
	GetWeaponComponent()->DestroyWeapon();
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
		Destroy();
		}), 3.0f, false);
}

void AP3Character::LevelUp()
{
	UP3GameInstance* P3GameInstance = Cast<UP3GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (P3GameInstance != nullptr)
	{
		int32 NextLevel = this->GetStatComponent()->GetLevel() + 1;
		FP3CharacterData* LevelBasedData = P3GameInstance->GetP3HeroData(NextLevel);
		GetStatComponent()->SetStatFromDataTable(NextLevel, LevelBasedData);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Character] GameInstance is NULL."))
	}
}

void AP3Character::Move(const FInputActionValue& Value)
{
	// when Character IsAttacking or IsUsingSkill, Can't Move.
	if (GetStateComponent()->GetbIsAttacking() || GetStateComponent()->GetbIsUsingSkill())
	{
		return;
	}

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AP3Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AP3Character::ShowDamageNumber(float NewDamageNumber)
{
	if (GetWorld())
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			// ���� Ǯ�� ����
			UP3DamageNumberWidget* DamageNumberWidget = CreateWidget<UP3DamageNumberWidget>(PlayerController, DamageNumberWidgetClass);
			if (DamageNumberWidget)
			{
				FVector2D WidgetPosition;
				UGameplayStatics::ProjectWorldToScreen(PlayerController, GetActorLocation(), WidgetPosition);
				DamageNumberWidget->SetPositionInViewport(WidgetPosition);
				DamageNumberWidget->SetDamageNumber(NewDamageNumber);
				DamageNumberWidget->AddToViewport();
			}
		}
	}
}

void AP3Character::DeleteTimer(FTimerHandle DeleteTimer)
{
	GetWorld()->GetTimerManager().ClearTimer(DeleteTimer);
}

void AP3Character::UpdateMaxWalkSpeed(float NewMaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxWalkSpeed;
}

void AP3Character::Heal(float Duration, float TotalHealAmount, UParticleSystem* NewParticle)
{
	if (Duration == 0.0f)
	{
		GetStatComponent()->TakeDamage(-1 * TotalHealAmount);
	}
	else
	{
		float RemainingTime = Duration;
		float HealPerSecond = TotalHealAmount / Duration;
		FName RootSocket(TEXT("Root"));
		UGameplayStatics::SpawnEmitterAttached(NewParticle, GetMesh(), RootSocket);
		GetStatComponent()->TakeDamage(-1 * HealPerSecond);	// To heal immediately when the skill starts.
		FTimerHandle HealTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, [this, RemainingTime, HealPerSecond, RootSocket, NewParticle, HealTimerHandle]()mutable -> void
			{
				if (--RemainingTime > 0)	// if Duration is 10.0f ,This if statement loops 9 times every second.
				{
					UGameplayStatics::SpawnEmitterAttached(NewParticle, GetMesh(), RootSocket);
					GetStatComponent()->TakeDamage(-1 * HealPerSecond);
				}
				else
				{
					DeleteTimer(HealTimerHandle);
				}
			}, 1.0f, true);
	}
}

void AP3Character::ManaRegen(float Duration, float TotalManaRegenAmount, UParticleSystem* NewParticle)
{
	if (Duration == 0.0f)
	{
		GetStatComponent()->ConsumeMP(-1 * TotalManaRegenAmount);
	}
	else
	{
		float RemainingTime = Duration;
		float ManaRegenPerSecond = TotalManaRegenAmount / Duration;
		FName RootSocket(TEXT("Root"));
		if (NewParticle != nullptr)
		{
			UGameplayStatics::SpawnEmitterAttached(NewParticle, GetMesh(), RootSocket);
		}
		GetStatComponent()->ConsumeMP(-1 * ManaRegenPerSecond);	// To ManaRegen immediately when the skill starts.
		FTimerHandle ManaRegenTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ManaRegenTimerHandle, [this, RemainingTime, ManaRegenPerSecond, RootSocket, NewParticle, ManaRegenTimerHandle]()mutable -> void
			{
				if (--RemainingTime > 0)	// if Duration is 10.0f ,This if statement loops 9 times every second.
				{
					if (NewParticle != nullptr)
					{
						UGameplayStatics::SpawnEmitterAttached(NewParticle, GetMesh(), RootSocket);
					}
					GetStatComponent()->ConsumeMP(-1 * ManaRegenPerSecond);
				}
				else
				{
					DeleteTimer(ManaRegenTimerHandle);
				}
			}, 1.0f, true);
	}
}

bool AP3Character::ConsumeMP(float UsedMP)
{
	float CalculatedMP = UsedMP;	// if character has buff/debuff, UsedMP can changed.
	if (GetStatComponent()->GetCurrentMP() < CalculatedMP)
	{
		return false;
	}
	GetStatComponent()->ConsumeMP(CalculatedMP);
	return true;
}

float AP3Character::ApplyDamage(AController* EventInstigator, AP3Character* EventInstigatorActor)
{
	if (EventInstigatorActor->GetStatComponent()->GetLevelBasedCurrentData() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Character] When TakeDamage Instigator's StatComponent doesn't have LevelBasedCurrentStat."));
		return 0.0f;
	}

	float InitialDamage = EventInstigatorActor->GetStatComponent()->GetAttack();

	// Team Judgment
	if (this->GetCharacterType() == ECharacterType::None || EventInstigatorActor->GetCharacterType() == ECharacterType::None)
	{
		return 0.0f;
	}

	if (this->GetCharacterType() == EventInstigatorActor->GetCharacterType())
	{
		return 0.0f;
	}

	// Damage logic : Damage = Attack (when defense stat update? will changed?)
	float FinalDamage = InitialDamage;	
	GetStatComponent()->TakeDamage(FinalDamage);

	ShowDamageNumber(FinalDamage);

	// Exp Logic
	if (GetStateComponent()->GetbIsDead())
	{
		// when Multiplay, Each PlayerController's bIsPlayerController is all true?
		if (EventInstigator->IsPlayerController())
		{
			if (this->GetCharacterType() == ECharacterType::Enemy)
			{
				UP3GameInstance* P3GameInstance = Cast<UP3GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
				if (P3GameInstance != nullptr)
				{
					float DroppedExp = P3GameInstance->GetP3EnemyData(this->GetStatComponent()->GetLevel())->DropExp;
					EventInstigatorActor->GetStatComponent()->AddExp(DroppedExp);
				}

				// Give Dropped Item in this->Inventory to EventInstigatorActor's Inventory.
				TArray<UP3Item*> DroppedItems = DropItem();
				for (int32 i = 0; i < DroppedItems.Num(); ++i)
				{
					EventInstigatorActor->AddItem(DroppedItems[i]);
				}
			}
		}
	}
	
	return FinalDamage;
}

void AP3Character::AddItem(UP3Item* AddedItem)
{
	GetInventoryComponent()->AddItem(AddedItem);
}

TArray<UP3Item*> AP3Character::DropItem()
{
	return GetInventoryComponent()->RemoveRandomItems();
}