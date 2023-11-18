#include "P3MPRegen.h"

UP3MPRegen::UP3MPRegen()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE_MPRegen(TEXT("/Game/GameData/Images/Image_HealMP.Image_HealMP"));
	if (IMAGE_MPRegen.Succeeded())
	{
		Image = IMAGE_MPRegen.Object;
	}

	BuffType = EBuffType::MPREGEN;
}	

void UP3MPRegen::InitBuffData(FString NewName, float NewDuration, float NewTotalAmount)
{
	Name = NewName;
	Duration = NewDuration;
	TotalAmount = NewTotalAmount;
}