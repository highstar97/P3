#include "P3HeroController.h"
#include "P3Character.h"
#include "P3SkillComponent.h"
#include "P3HUDWidget.h"
#include "P3InventoryWidget.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AP3HeroController::AP3HeroController()
{
	static ConstructorHelpers::FClassFinder<UP3HUDWidget> UI_HUD_C(TEXT("/Game/Blueprints/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UP3InventoryWidget> UI_INVENTORY_C(TEXT("/Game/Blueprints/UI/UI_Inventory.UI_Inventory_C"));
	if (UI_INVENTORY_C.Succeeded())
	{
		InventoryWidgetClass = UI_INVENTORY_C.Class;
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT(TEXT("/Game/Input/IMC_Default.IMC_Default"));
	if (IMC_DEFAULT.Succeeded())
	{
		DefaultMappingContext = IMC_DEFAULT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_OPENINVENTORY(TEXT("/Game/Input/Actions/IA_OpenInventory.IA_OpenInventory"));
	if (IA_OPENINVENTORY.Succeeded())
	{
		OpenInventoryAction = IA_OPENINVENTORY.Object;
	}
}

void AP3HeroController::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (HUDWidgetClass != nullptr)
	{
		HUDWidget = CreateWidget<UP3HUDWidget>(this, HUDWidgetClass);
		AP3Character* P3Character = Cast<AP3Character>(GetCharacter());
		if (P3Character != nullptr)
		{
			FString Skill1Name = P3Character->GetSkillComponent()->GetSkill1Name();
			FString Skill2Name = P3Character->GetSkillComponent()->GetSkill2Name();
			HUDWidget->InitHUDWidget(Skill1Name, Skill2Name);
		}
		HUDWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HeroController] HUDWidgetClass is null."));
	}

	if (InventoryWidgetClass != nullptr)
	{
		InventoryWidget = CreateWidget<UP3InventoryWidget>(this, InventoryWidgetClass);
		// InventoryWidget->Update();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HeroController] InventoryWidget is null."));
	}
}

void AP3HeroController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AP3HeroController::OnPossess(APawn* APawn)
{
	Super::OnPossess(APawn);
}

void AP3HeroController::OpenInventory()
{
	// Close Inventory
	if (InventoryWidget->IsVisible())
	{
		SetPause(false);
		SetInputMode(OnlyGameInputMode);
		bShowMouseCursor = false;
		InventoryWidget->RemoveFromParent();
	}
	// Open Inventory
	else
	{
		SetPause(true);
		SetInputMode(GameAndUIInputMode);
		bShowMouseCursor = true;
		InventoryWidget->AddToViewport();
	}
}

void AP3HeroController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(OpenInventoryAction, ETriggerEvent::Triggered, this, &AP3HeroController::OpenInventory);
	}
}