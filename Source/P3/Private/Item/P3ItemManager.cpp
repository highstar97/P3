#include "P3ItemManager.h"
#include "P3GameInstance.h"
#include "P3Item.h"
#include "P3HPPotion_Small.h"
#include "P3MPPotion_Small.h"

UP3ItemManager::UP3ItemManager()
{
	
}

void UP3ItemManager::Init(UP3GameInstance* GameInstance)
{
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3ItemManager] : Can't Access to P3GameInstance."));
		return;
	}

	UP3Item* HPPotion_Small = NewObject<UP3HPPotion_Small>(this, FName("HPPotion_Small"));
	HPPotion_Small->UpdateItem(GameInstance);
	ItemMap.Emplace(HPPotion_Small->GetKey(), HPPotion_Small);

	UP3Item* MPPotion_Small = NewObject<UP3MPPotion_Small>(this, FName("MPPotion_Small"));
	MPPotion_Small->UpdateItem(GameInstance);
	ItemMap.Emplace(MPPotion_Small->GetKey(), MPPotion_Small);
}

UP3Item* UP3ItemManager::GetItemByKey(int32 ItemKey)
{
	if (ItemMap.Contains(ItemKey))
	{
		return ItemMap[ItemKey];
	}
	else
	{
		return nullptr;
	}
}