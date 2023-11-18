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

	CurrentGameInstance = GameInstance;

	if (!CreateHPPotion_Small())
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3ItemManager] : Can't Create HPPotion_Small."));
	}

	if (!CreateMPPotion_Small())
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3ItemManager] : Can't Create HPPotion_Small."));
	}
}

bool UP3ItemManager::CreateHPPotion_Small()
{
	UP3Item* HPPotion_Small = NewObject<UP3HPPotion_Small>(this, FName("HPPotion_Small"));
	if (HPPotion_Small->InitItemData(HPPotion_Small->GetItemData(CurrentGameInstance.Get())))
	{
		ItemMap.Emplace(HPPotion_Small->GetKey(), HPPotion_Small);
		return true;
	}
	return false;
}

bool UP3ItemManager::CreateMPPotion_Small()
{
	UP3Item* MPPotion_Small = NewObject<UP3MPPotion_Small>(this, FName("MPPotion_Small"));
	if (MPPotion_Small->InitItemData(MPPotion_Small->GetItemData(CurrentGameInstance.Get())))
	{
		ItemMap.Emplace(MPPotion_Small->GetKey(), MPPotion_Small);
		return true;
	}
	return false;
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