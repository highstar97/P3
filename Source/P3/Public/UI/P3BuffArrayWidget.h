#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3BuffArrayWidget.generated.h"

class UP3Buff;
class UTileView;

UCLASS()
class P3_API UP3BuffArrayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void AddBuff(UP3Buff* AddedBuff);
	void RemoveBuff(UP3Buff* RemovedBuff);

private:
	UPROPERTY(meta = (BindWidget))
		UTileView* Tile_Buffs;
};
