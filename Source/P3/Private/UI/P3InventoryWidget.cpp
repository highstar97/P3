#include "P3InventoryWidget.h"
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
	}
}

void UP3InventoryWidget::AddItem(UP3Item* AddedItem)
{
	Tile_Items->AddItem(AddedItem);
}

void UP3InventoryWidget::RemoveItem(UP3Item* RemovedItem)
{
	Tile_Items->RemoveItem(RemovedItem);
}