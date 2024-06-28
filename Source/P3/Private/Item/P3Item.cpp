#include "P3Item.h"
#include "P3ItemManager.h"
#include "P3Character.h"

UP3Item::~UP3Item()
{

}

void UP3Item::Use(AP3Character* User)
{

}

// must be called in consturctor, because of ConstructorHelpers
void UP3Item::ConstructItemFromData(const FP3ItemData* ItemData)
{
	SetKey(ItemData->Key);
	SetName(ItemData->Name);
	ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE(*ItemData->Path);
	if (IMAGE.Succeeded())
	{
		SetImage(IMAGE.Object);
	}
	SetType(ItemData->Type);
}