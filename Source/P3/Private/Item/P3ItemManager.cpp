#include "P3ItemManager.h"
#include "P3Item.h"
#include "P3GameInstance.h"
#include "Kismet/GameplayStatics.h"

UP3ItemManager::UP3ItemManager()
{
	
}

void UP3ItemManager::Init(UP3GameInstance* GameInstance)
{
	//UP3GameInstance* GameInstance = Cast<UP3GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3ItemManager] : Can't Access to P3GameInstance."));
		return;
	}
	else
	{
		if (ItemMap.Num() == GameInstance->GetNumOfP3ItemDataTable())
		{
			return;
		}

		for (int32 i = 1; i <= GameInstance->GetNumOfP3ItemDataTable(); ++i)
		{
			FP3ItemData* ItemData = GameInstance->GetP3ItemData(i);
			UP3Item* Item = NewObject<UP3Item>(this, FName(ItemData->Name));
			Item->SetKey(ItemData->Key);
			Item->SetName(ItemData->Name);
			ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE(*ItemData->Path);
			if (IMAGE.Succeeded())
			{
				Item->SetImage(IMAGE.Object);
			}
			Item->SetType(ItemData->Type);
			ItemMap.Emplace(i, Item);
		}
	}
}

UP3Item* UP3ItemManager::GetItemByKey(int32 ItemKey)
{
	if (ItemMap.Contains(ItemKey))
	{
		return ItemMap[ItemKey];
	}
	else
	{
		return nullptr;
	}
}