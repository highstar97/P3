#include "P3BuffManager.h"

#include "P3Buff.h"

UP3BuffManager::UP3BuffManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_P3Buff(TEXT("/Game/GameData/P3BuffData.P3BuffData"));
	if (DT_P3Buff.Succeeded())
	{
		P3BuffDataTable = DT_P3Buff.Object;
		if (P3BuffDataTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogAssetData, Warning, TEXT("[P3BuffManager] No data inside P3BuffDataTable."));
		}
	}
}

void UP3BuffManager::InitializeBuffs()
{
	if (!P3BuffDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3BuffManager] P3BuffDataTable is not set."));
		return;
	}

	TArray<FP3BuffData*> AllDatas;
	P3BuffDataTable->GetAllRows(TEXT("P3BuffDataTable"), AllDatas);

	for (const FP3BuffData* Data : AllDatas)
	{
		if (Data)
		{
			UP3Buff* NewBuff = NewObject<UP3Buff>(this);
			if (NewBuff)
			{
				NewBuff->ConstructBuffFromData(Data);
				BuffMap.Emplace(Data->Key, NewBuff);
			}
		}
	}
}

UP3Buff* UP3BuffManager::GetBuffByKey(int32 BuffKey) const
{
	if (BuffMap.Contains(BuffKey))
	{
		return BuffMap[BuffKey];
	}
	else
	{
		return nullptr;
	}
}