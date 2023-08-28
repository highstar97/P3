#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "P3ItemImageWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class P3_API UP3ItemImageWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UPROPERTY(meta = (BindWidget))
		UImage* Image_Item;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_NumOfItems;
};