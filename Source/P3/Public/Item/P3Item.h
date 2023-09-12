#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "P3Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE		UMETA(DisplayName = "None"),
	WEAPON		UMETA(DisplayName = "Weapon"),
	CONSUMABLE	UMETA(DisplayName = "Consumable"),
	JUNK		UMETA(DisplayName = "Junk")
};

UCLASS()
class P3_API UP3Item : public UObject
{
	GENERATED_BODY()
	
public:
	UP3Item();
	virtual ~UP3Item();

	int32 GetKey() const { return Key; }
	void SetKey(int32 NewKey) { Key = NewKey; }

	FString GetName() const { return Name; }
	void SetName(FString Newname) { Name = Newname; }

	UTexture2D* GetImage() const { return Image; }
	void SetImage(UTexture2D* NewImage) { Image = NewImage; }

	EItemType GetType() const { return Type; }
	void SetType(EItemType NewType) { Type = NewType; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
		int32 Key;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
		FString Name;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
		UTexture2D* Image;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
		EItemType Type;
};