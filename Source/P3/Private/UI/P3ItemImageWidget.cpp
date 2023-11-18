#include "P3ItemImageWidget.h"
#include "P3HeroController.h"
#include "P3Item.h"
#include "P3InventoryWidget.h"
#include "P3InventoryComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UP3ItemImageWidget::SyncItemWithInventory(UP3Item* ItemToSync)
{
	AP3HeroController* HeroController = Cast<AP3HeroController>(GetOwningPlayer());
	if (HeroController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3ItemImageWidget] : Can't Cast to HeroController."));
		return;
	}
	UP3InventoryWidget* InventoryWidget = HeroController->GetInventoryWidget();
	if (InventoryWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3ItemImageWidget] : Can't Access to InventoryWidget."));
		return;
	}
	FP3ItemInfo* InsertedItemInfo = InventoryWidget->GetCurrentInventoryComponent()->FindItemInfo(ItemToSync);
	if (InsertedItemInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3ItemImageWidget] : Can't Find Info about AddedItem."));
		return;
	}

	NumOfInsertedItem = InsertedItemInfo->Num;
	InsertedItem = InsertedItemInfo->Item;
	Texture2D_Item = InsertedItemInfo->Item->GetImage();
	Image_Item->SetBrushFromTexture(Texture2D_Item);
	Text_NumOfItems->SetText(FText::FromString(FString::FromInt(InsertedItemInfo->Num)));
}

void UP3ItemImageWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{	
	check(ListItemObject != nullptr);
	UP3Item* Item = Cast<UP3Item>(ListItemObject);
	SyncItemWithInventory(Item);
}

void UP3ItemImageWidget::OnListItemObjectSet(UObject* ListItemObject)
{
	check(ListItemObject != nullptr);
}