#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "P3ItemImageWidget.generated.h"

class UP3Item;
class UImage;
class UTextBlock;

UCLASS()
class P3_API UP3ItemImageWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	void SyncItemWithInventory(UP3Item* ItemToSync);

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Image_Item;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TextBlock_Quantity;
};