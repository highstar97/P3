#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "P3ItemImageWidget.generated.h"

class UP3Item;
class UTexture2D;
class UImage;
class UTextBlock;

UCLASS()
class P3_API UP3ItemImageWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UP3Item* GetInsertedItem() const { return InsertedItem; }

	void SyncItemWithInventory(UP3Item* ItemToSync);

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void OnListItemObjectSet(UObject* ListItemObject);

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 NumOfInsertedItem;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UP3Item* InsertedItem;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTexture2D* Texture2D_Item;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UImage* Image_Item;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* Text_NumOfItems;
};