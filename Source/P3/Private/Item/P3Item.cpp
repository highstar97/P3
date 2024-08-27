#include "Item/P3Item.h"

#include "P3GameInstance.h"
#include "Character/P3Character.h"
#include "Component/P3InventoryComponent.h"
#include "Component/P3BuffComponent.h"
#include "Item/P3ItemManager.h"
#include "Buff/P3BuffManager.h"
#include "Buff/P3Buff.h"

void UP3Item::Use(AP3Character* User)
{
	UWorld* World = User->GetWorld();

	UP3GameInstance* P3GameInstance = Cast<UP3GameInstance>(World->GetGameInstance());

	UP3BuffManager* BuffManager = P3GameInstance->GetBuffManager();
	UP3InventoryComponent* InventoryComponent = User->GetInventoryComponent();
	UP3BuffComponent* BuffComponent = User->GetBuffComponent();
	
	for (const int32 BuffKey : BuffKeyArray)
	{
		UP3Buff* BuffToAdd = BuffManager->GetBuffByKey(BuffKey)->CreateCopy();
		if (BuffToAdd && BuffComponent->AddBuff(BuffToAdd))
		{
			InventoryComponent->RemoveItem(this);
			return;
		}
	}
}

// must be called in consturctor, because using ConstructorHelpers
void UP3Item::ConstructItemFromData(const FP3ItemData* ItemData)
{
	SetKey(ItemData->Key);
	SetName(ItemData->Name);
	ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE(*ItemData->TexturePath);
	if (IMAGE.Succeeded())
	{
		SetImage(IMAGE.Object);
	}
	SetType(ItemData->Type);
	SetBuffKeyArray(ItemData->BuffKeyArray);
}