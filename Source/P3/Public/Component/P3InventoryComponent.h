#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3Item.h"
#include "P3InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemAddedDelegate, UP3Item*);

USTRUCT(BlueprintType)
struct FP3ItemInfo
{
	GENERATED_BODY()

public:
	FP3ItemInfo() : Item(nullptr), Num(0) {}

	friend bool operator==(const FP3ItemInfo &InfoA, const FP3ItemInfo &InfoB)
	{
		if (InfoA.Item == InfoB.Item && InfoA.Num == InfoB.Num)
		{
			return true;
		}
		return false;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		UP3Item* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 Num;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UP3InventoryComponent();

	void AddItem(UP3Item* AddedItem, int32 NumOfItem = 1);
	UP3Item* RemoveItem(UP3Item* RemovedItem);

	FP3ItemInfo* FindItemInfo(UP3Item* FindItem);

	TArray<UP3Item*> RemoveRandomItems();

	FOnItemAddedDelegate OnItemAdded;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
		TArray<FP3ItemInfo> Inventory;
};