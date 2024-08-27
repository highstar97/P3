#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "P3Buff.h"
#include "P3BuffManager.generated.h"

class UP3Buff;

USTRUCT(BlueprintType)
struct FP3BuffData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FP3BuffData() : Key(0), Name(""), NumericData(FNumericData()), TagContainer(FGameplayTagContainer::EmptyContainer), TexturePath(""), ParticlePath("") {}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	int32 Key;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FNumericData NumericData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FGameplayTagContainer TagContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FString TexturePath;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FString ParticlePath;
};

UCLASS()
class P3_API UP3BuffManager : public UObject
{
	GENERATED_BODY()

public:
	UP3BuffManager();

	void InitializeBuffs();

	UP3Buff* GetBuffByKey(int32 BuffKey) const;

private:
	UPROPERTY()
	TObjectPtr<UDataTable> P3BuffDataTable;

	UPROPERTY()
	TMap<int32, UP3Buff*> BuffMap;
};