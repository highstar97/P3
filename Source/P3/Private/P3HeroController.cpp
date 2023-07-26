#include "P3HeroController.h"
#include "P3Character.h"
#include "P3SkillComponent.h"
#include "P3HUDWidget.h"

AP3HeroController::AP3HeroController()
{
	static ConstructorHelpers::FClassFinder<UP3HUDWidget> UI_HUD_C(TEXT("/Game/Blueprints/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
}

void AP3HeroController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		HUDWidget = CreateWidget<UP3HUDWidget>(this, HUDWidgetClass);
		AP3Character* P3Character = Cast<AP3Character>(GetCharacter());
		if (P3Character != nullptr)
		{
			FString Skill1Name = P3Character->GetSkillComponent()->GetSkill1Name();
			HUDWidget->InitHUDWidget(Skill1Name);
		}
		HUDWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HeroController] HUDWidgetClass is null."));
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