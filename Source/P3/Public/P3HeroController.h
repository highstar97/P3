#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P3HeroController.generated.h"

class UP3HUDWidget;

UCLASS()
class P3_API AP3HeroController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AP3HeroController();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* APawn) override;

	UP3HUDWidget* GetHUDWidget() const { return HUDWidget; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UP3HUDWidget> HUDWidgetClass;

	UPROPERTY()
		UP3HUDWidget* HUDWidget;
};
