#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P3GameMode.generated.h"

UCLASS(minimalapi)
class AP3GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AP3GameMode();

	virtual void PostLogin(APlayerController* NewPlayer);
};