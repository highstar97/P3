#include "P3HPPotion_Small.h"

UP3HPPotion_Small::UP3HPPotion_Small()
{
	Name = "HPPotion_Small";
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE_HPPOTION_SMALL(TEXT("/Game/GameData/Images/Image_HPPotion_Small.Image_HPPotion_Small"));
	if (IMAGE_HPPOTION_SMALL.Succeeded())
	{
		Image = IMAGE_HPPOTION_SMALL.Object;
	}
}