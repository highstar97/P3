#include "P3GameMode.h"
#include "P3Hero.h"
#include "P3HeroController.h"
#include "UObject/ConstructorHelpers.h"

AP3GameMode::AP3GameMode()
{
	DefaultPawnClass = AP3Hero::StaticClass();
	PlayerControllerClass = AP3HeroController::StaticClass();
}

void AP3GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}