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

bool UP3Item::InitItemData(FP3ItemData* ItemDataReference)
{
	if (ItemDataReference == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3Item] : Can't Load ItemData. Check Key."));
		return false;
	}

	this->SetName(ItemDataReference->Name);
	ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE(*ItemDataReference->Path);
	if (IMAGE.Succeeded())
	{
		this->SetImage(IMAGE.Object);
	}
	this->SetType(ItemDataReference->Type);
	return true;
}

FP3ItemData* UP3Item::GetItemData(UP3GameInstance* GameInstance)
{
	FP3ItemData* ItemData = GameInstance->GetP3ItemData(this->GetKey());
	if (ItemData == nullptr)
	{
		return nullptr;
	}
	return ItemData;
}