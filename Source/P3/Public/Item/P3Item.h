#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "P3Item.generated.h"

struct FP3ItemData;
class UP3GameInstance;
class AP3Character;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None		UMETA(DisplayName = "None"),
	Weapon		UMETA(DisplayName = "Weapon"),
	Consumable	UMETA(DisplayName = "Consumable"),
	Junk		UMETA(DisplayName = "Junk")
};

UCLASS(BlueprintType)
class P3_API UP3Item : public UObject
{
	GENERATED_BODY()

public:
	UP3Item() : Key(-1), Name("ItemBase"), Image(nullptr), Type(EItemType::None) {};

	UFUNCTION(BlueprintCallable)
	void Use(AP3Character* User);

	void ConstructItemFromData(const FP3ItemData* ItemData);

	FORCEINLINE int32 GetKey() const { return Key; }
	FORCEINLINE void SetKey(const int32 NewKey) { Key = NewKey; }

	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& NewName) { Name = NewName; }

	FORCEINLINE UTexture2D* GetImage() const { return Image; }
	FORCEINLINE void SetImage(UTexture2D* NewImage) { Image = NewImage; }

	FORCEINLINE EItemType GetType() const { return Type; }
	FORCEINLINE void SetType(const EItemType NewType) { Type = NewType; }

	FORCEINLINE TArray<int32> GetBuffKeyArray() const { return BuffKeyArray; }
	FORCEINLINE void SetBuffKeyArray(const TArray<int32>& NewBuffKeyArray) { BuffKeyArray.Append(NewBuffKeyArray); }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	int32 Key;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> Image;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	EItemType Type;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TArray<int32> BuffKeyArray;
};