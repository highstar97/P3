#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "P3BuffImageWidget.generated.h"

class UImage;

UCLASS()
class P3_API UP3BuffImageWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:	
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Buff;
};