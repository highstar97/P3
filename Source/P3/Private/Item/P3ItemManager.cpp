#include "P3ItemManager.h"
#include "P3GameInstance.h"
#include "P3Item.h"
#include "P3HPPotion_Small.h"
#include "P3MPPotion_Small.h"

UP3ItemManager::UP3ItemManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_P3Item(TEXT("/Game/GameData/P3ItemData.P3ItemData"));
	if (DT_P3Item.Succeeded())
	{
		P3ItemDataTable = DT_P3Item.Object;
		if (P3ItemDataTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogAssetData, Warning, TEXT("[P3ItemManager] No data inside P3ItemDataTable."));
		}
	}
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

FP3ItemData* UP3ItemManager::GetItemDataFromDataTable(int32 KeyOfItem) const
{
	return P3ItemDataTable->FindRow<FP3ItemData>(*FString::FromInt(KeyOfItem), TEXT(""));
}

void UP3ItemManager::InitializeItems()
{
	if (!P3ItemDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3ItemManager] P3ItemDataTable is not set."));
		return;
	}

	TArray<FP3ItemData*> AllDatas;
	P3ItemDataTable->GetAllRows(TEXT("P3ItemDataTable"), AllDatas);

	for (const FP3ItemData* Data : AllDatas)
	{
		if (Data && Data->ItemClass)
		{
			UP3Item* NewItem = NewObject<UP3Item>(this, Data->ItemClass);
			if (NewItem)
			{
				NewItem->ConstructItemFromData(Data);
				ItemMap.Emplace(Data->Key, NewItem);
			}
		}
	}
}