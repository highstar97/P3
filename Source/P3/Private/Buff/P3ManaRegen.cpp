#include "P3ManaRegen.h"

UP3ManaRegen::UP3ManaRegen()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE_MANAREGEN(TEXT("/Game/GameData/Images/Image_HealMP.Image_HealMP"));
	if (IMAGE_MANAREGEN.Succeeded())
	{
		Image = IMAGE_MANAREGEN.Object;
	}

	BuffType = EBuffType::MANAREGEN;
}

void UP3ManaRegen::InitManaRegen(FString NewName, float NewDuration, float NewTotaManaRegenAmount)
{
	Name = NewName;
	Duration = NewDuration;
	TotalManaRegenAmount = NewTotaManaRegenAmount;
}