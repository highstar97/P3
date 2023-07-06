#include "P3Character.h"
#include "P3HeroController.h"
#include "P3StatComponent.h"
#include "P3StateComponent.h"
#include "P3WeaponComponent.h"
#include "P3GameInstance.h"
#include "P3HUDWidget.h"
#include "P3HPBarWidget.h"
#include "P3Weapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
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

	HPBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HPBarWidgetComponent->SetupAttachment(RootComponent);
	HPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBAR(TEXT("/Game/Blueprints/UI/UI_HPBar.UI_HPBar_C"));
	if (UI_HPBAR.Succeeded())
	{
		HPBarWidgetComponent->SetWidgetClass(UI_HPBAR.Class);
		HPBarWidgetComponent->SetDrawSize(FVector2D(100.0f, 30.0f));
	}

	StatComponent = CreateDefaultSubobject<UP3StatComponent>(TEXT("StatComponent"));
	StateComponent = CreateDefaultSubobject<UP3StateComponent>(TEXT("StateComponent"));
	WeaponComponent = CreateDefaultSubobject<UP3WeaponComponent>(TEXT("WeaponComponent"));

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

		HeroController->GetHUDWidget()->BindCharacterStat(StatComponent);
	}
	
	AP3Weapon* CurrentWeapon = WeaponComponent->SpawnBasicSword();
	if (CurrentWeapon != nullptr)
	{
		WeaponComponent->EquipWeapon(CurrentWeapon);
	}

	UP3HPBarWidget* HPBarWidget = Cast<UP3HPBarWidget>(HPBarWidgetComponent->GetUserWidgetObject());
	if (HPBarWidget != nullptr)
	{
		HPBarWidget->BindCharacterStat(StatComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Character] HPBarWidget is NULL."));
	}
	
	InitStat();
}

void AP3Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AP3Character::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AP3Character::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AP3Character::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AP3Character::Look);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AP3Character::Attack);
	}
}

void AP3Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StatComponent->OnHPIsZero.AddUObject(this, &AP3Character::Die);
	StatComponent->OnLevelUp.AddUObject(this, &AP3Character::LevelUp);
}

void AP3Character::Jump()
{
	StateComponent->SetbIsInAir(true);
	Super::Jump();
}

void AP3Character::StopJumping()
{
	StateComponent->SetbIsInAir(false);
	Super::StopJumping();
}

void AP3Character::InitStat()
{
	
}

void AP3Character::Attack()
{
	
}

void AP3Character::Die()
{
	FTimerHandle DeadTimerHandle = {};
	StateComponent->SetbIsDead(true);
	SetActorEnableCollision(false);
	HPBarWidgetComponent->SetHiddenInGame(true);
	WeaponComponent->DestroyWeapon();
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
	// when Character IsAttacking, Can't Move.
	if (StateComponent->GetbIsAttacking())
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

void AP3Character::UpdateMaxWalkSpeed(float NewMaxWalkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxWalkSpeed;
}

float AP3Character::ApplyDamage(AController* EventInstigator, AP3Character* EventInstigatorActor)
{
	if (EventInstigatorActor->StatComponent->GetLevelBasedCurrentData() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Character] When TakeDamage Instigator's StatComponent doesn't have LevelBasedCurrentStat."));
		return 0.0f;
	}

	float InitialDamage = EventInstigatorActor->StatComponent->GetAttack();

	// Team Judgment
	if (this->GetCharacterType() == ECharacterType::None || EventInstigatorActor->GetCharacterType() == ECharacterType::None)
	{
		return 0.0f;
	}

	if (this->GetCharacterType() == EventInstigatorActor->GetCharacterType())
	{
		return 0.0f;
	}

	float FinalDamage = this->StatComponent->TakeDamage(InitialDamage);

	// Exp Logic
	if (this->StateComponent->GetbIsDead())
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
			}
		}
	}
	
	return FinalDamage;
}