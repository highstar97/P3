#include "P3ItemImageWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "P3Character.h"
#include "P3InventoryComponent.h"
#include "P3Item.h"

void UP3ItemImageWidget::SyncItemWithInventory(UP3Item* ItemToSync)
{
	FP3ItemInfo* InsertedItemInfo = Cast<AP3Character>(GetOwningPlayerPawn())->GetInventoryComponent()->FindItemInfo(ItemToSync);
	if (InsertedItemInfo != nullptr)
	{
		Image_Item->SetBrushFromTexture(InsertedItemInfo->Item->GetImage());
		TextBlock_Quantity->SetText(FText::FromString(FString::FromInt(InsertedItemInfo->Num)));
	}
}

void UP3ItemImageWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{	
	UP3Item* Item = Cast<UP3Item>(ListItemObject);
	
	SyncItemWithInventory(Item);
}