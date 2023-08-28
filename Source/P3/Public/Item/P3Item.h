#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "P3Item.generated.h"

UCLASS()
class P3_API UP3Item : public UObject
{
	GENERATED_BODY()
	
public:
	UP3Item();
	virtual ~UP3Item();

	FString GetName() const { return Name; }
	UTexture2D* GetImage() const { return Image; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
		FString Name;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
		UTexture2D* Image;
};