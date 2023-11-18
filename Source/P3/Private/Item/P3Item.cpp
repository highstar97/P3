#include "P3Item.h"
#include "P3GameInstance.h"
#include "P3Character.h"

UP3Item::UP3Item()
{
	Key = 0;
	Name = "Item";
	Image = nullptr;
	Type = EItemType::NONE;
}

UP3Item::~UP3Item()
{

}

void UP3Item::Use(AP3Character* User)
{

}

void UP3Item::UpdateItem(UP3GameInstance* GameInstance)
{
	FP3ItemData* ItemData = GameInstance->GetP3ItemData(this->GetKey());
	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Item] : Can't Load ItemData. Check Key."));
		return;
	}

	this->SetName(ItemData->Name);
	ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE(*ItemData->Path);
	if (IMAGE.Succeeded())
	{
		this->SetImage(IMAGE.Object);
	}

	this->SetType(ItemData->Type);
}