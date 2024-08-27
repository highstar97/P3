#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "P3Item.h"
#include "P3ItemManager.generated.h"

class UDataTable;
class UP3Buff;

USTRUCT(BlueprintType)
struct FP3ItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FP3ItemData() : Key(0), Name(""), TexturePath(""), Type(EItemType::None), BuffKeyArray({}) {}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	int32 Key;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FString TexturePath;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	TArray<int32> BuffKeyArray;
};

UCLASS()
class P3_API UP3ItemManager : public UObject
{
	GENERATED_BODY()

public:
	UP3ItemManager();

	void InitializeItems();

    UFUNCTION(BlueprintCallable, Category = "Item")
    UP3Item* GetItemByKey(int32 ItemKey) const;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> P3ItemDataTable;

    UPROPERTY()
    TMap<int32, TObjectPtr<UP3Item>> ItemMap;	// TODO : Change it to Cache.
};