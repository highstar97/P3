// Copyright Epic Games, Inc. All Rights Reserved.

#include "P3GameMode.h"
#include "P3Character.h"
#include "UObject/ConstructorHelpers.h"

AP3GameMode::AP3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
