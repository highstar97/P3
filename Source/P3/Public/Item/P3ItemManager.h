#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "P3Item.h"
#include "P3ItemManager.generated.h"

class UP3GameInstance;
class UDataTable;

USTRUCT(BlueprintType)
struct FP3ItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FP3ItemData() : Key(0), Name(""), Path(""), Type(EItemType::NONE), ItemClass(nullptr) {}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	int32 Key;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	FString Path;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	TSubclassOf<UP3Item> ItemClass;
};

UCLASS()
class P3_API UP3ItemManager : public UObject
{
	GENERATED_BODY()

public:
	UP3ItemManager();

	void InitializeItems();

    UFUNCTION(BlueprintCallable, Category = "Item")
    UP3Item* GetItemByKey(int32 ItemKey);

	FORCEINLINE FP3ItemData* GetItemDataFromDataTable(int32 KeyOfItem) const;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> P3ItemDataTable;

    UPROPERTY()
    TMap<int32, UP3Item*> ItemMap;
};