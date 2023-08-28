#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3InventoryWidget.generated.h"

class UP3Item;
class UTileView;

UCLASS()
class P3_API UP3InventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddItem(UP3Item* AddedItem);
	void RemoveItem(UP3Item* RemovedItem);

private:
	UPROPERTY(meta = (BindWidget))
		UTileView* Tile_Items;
};