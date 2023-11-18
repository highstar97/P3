#include "P3InventoryComponent.h"
#include "P3Item.h"

UP3InventoryComponent::UP3InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Inventory.Empty();
}

void UP3InventoryComponent::AddItem(UP3Item* ItemToAdd, int32 NumOfItem)
{
	// If there is a unique item that only exists, an if statement must be added.
	if (ItemToAdd->GetType() == EItemType::NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3InventoryComponent] : Wrong Item Added."));
	}
	else
	{
		FP3ItemInfo* FoundElement = FindItemInfo(ItemToAdd);

		if (FoundElement)
		{
			FoundElement->Num += NumOfItem;
			OnItemChanged.Broadcast(ItemToAdd);
		}
		else
		{
			FP3ItemInfo TempInfo;
			TempInfo.Item = ItemToAdd;
			TempInfo.Num = NumOfItem;
			Inventory.Emplace(TempInfo);
			OnItemAdded.Broadcast(ItemToAdd);
		}
	}
}

UP3Item* UP3InventoryComponent::RemoveItem(UP3Item* ItemToRemove)
{
	FP3ItemInfo* FoundElement = FindItemInfo(ItemToRemove);

	if (FoundElement)
	{
		if (FoundElement->Num > 0)
		{
			FoundElement->Num -= 1;
			// When Remove Last Item. Remove Item on Inventory Widget.
			if (FoundElement->Num <= 0)
			{
				OnItemRemoved.Broadcast(FoundElement->Item);
				Inventory.RemoveSingle(*FoundElement);
			}
			else
			{
				OnItemChanged.Broadcast(FoundElement->Item);
			}
			return FoundElement->Item;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("[P3InventoryComponent] : ItemToRemove doesn't exsist."));
	return nullptr;
}

// Find Item in Inventory.
FP3ItemInfo* UP3InventoryComponent::FindItemInfo(UP3Item* ItemToFind)
{
	int32 KeyToFind = ItemToFind->GetKey();
	FP3ItemInfo* FoundElement = Inventory.FindByPredicate([KeyToFind](const FP3ItemInfo& Info) {
		return Info.Item->GetKey() == KeyToFind;
		});

	if (FoundElement)
	{
		return FoundElement;
	}
	else
	{
		return nullptr;
	}
}

TArray<UP3Item*> UP3InventoryComponent::RemoveRandomItems()
{
	TArray<UP3Item*> DroppedItemArray;
	int32 NumOfItemTypesToDrop = FMath::RandRange(1, Inventory.Num());
	for (int32 i = 0; i < NumOfItemTypesToDrop; ++i)
	{
		int32 NumOfItemsToDrop = FMath::RandRange(1, Inventory[i].Num);
		for (int32 j = 0; j < NumOfItemsToDrop; ++j)
		{
			DroppedItemArray.Emplace(RemoveItem(Inventory[i].Item));
		}
	}
	return DroppedItemArray;
}

void UP3InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}