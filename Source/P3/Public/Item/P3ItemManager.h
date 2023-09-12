#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "P3ItemManager.generated.h"

class UP3GameInstance;
class UP3Item;

UCLASS()
class P3_API UP3ItemManager : public UObject
{
	GENERATED_BODY()

public:
    UP3ItemManager();

    void Init(UP3GameInstance* GameInstance);

    UFUNCTION(BlueprintCallable, Category = "Item")
        UP3Item* GetItemByKey(int32 ItemKey);

private:
    UPROPERTY()
        TMap<int32, UP3Item*> ItemMap;
};