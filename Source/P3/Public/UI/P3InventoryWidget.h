#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3InventoryWidget.generated.h"

class UP3InventoryComponent;
class UP3Item;
class UTileView;

UCLASS()
class P3_API UP3InventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindInventory(UP3InventoryComponent* NewInventoryComponent);

	UP3InventoryComponent* GetCurrentInventoryComponent() { return CurrentInventoryComponent.Get(); }

	void AddItem(UP3Item* AddedItem);
	void RemoveItem(UP3Item* RemovedItem);

private:
	TWeakObjectPtr<UP3InventoryComponent> CurrentInventoryComponent = nullptr;

	UPROPERTY(meta = (BindWidget))
		UTileView* Tile_Items;
};