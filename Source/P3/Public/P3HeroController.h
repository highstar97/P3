#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P3HeroController.generated.h"

UCLASS()
class P3_API AP3HeroController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* APawn) override;
};
