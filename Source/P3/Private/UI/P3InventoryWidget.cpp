#include "P3InventoryWidget.h"
#include "P3HeroController.h"
#include "P3ItemImageWidget.h"
#include "P3InventoryComponent.h"
#include "P3Item.h"
#include "Components/TileView.h"

void UP3InventoryWidget::BindInventory(UP3InventoryComponent* NewInventoryComponent)
{
	if (NewInventoryComponent != nullptr)
	{
		CurrentInventoryComponent = NewInventoryComponent;
		CurrentInventoryComponent->OnItemAdded.AddUObject(this, &UP3InventoryWidget::AddItem);
		CurrentInventoryComponent->OnItemRemoved.AddUObject(this, &UP3InventoryWidget::RemoveItem);
		CurrentInventoryComponent->OnItemChanged.AddUObject(this, &UP3InventoryWidget::UpdateItem);
	}
}

void UP3InventoryWidget::AddItem(UP3Item* ItemToAdd)
{
	Tile_Items->AddItem(ItemToAdd);
}

void UP3InventoryWidget::RemoveItem(UP3Item* ItemToRemove)
{
	Tile_Items->RemoveItem(ItemToRemove);
}

void UP3InventoryWidget::UpdateItem(UP3Item* ItemToUpdate)
{
	for (auto EntryWidget : Tile_Items->GetDisplayedEntryWidgets())
	{
		UP3ItemImageWidget* ItemImageWidget = Cast<UP3ItemImageWidget>(EntryWidget);
		ItemImageWidget->SyncItemWithInventory(ItemImageWidget->GetInsertedItem());
	}
}