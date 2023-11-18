#include "P3HPPotion_Small.h"
#include "P3GameInstance.h"
#include "P3Character.h"
#include "P3BuffComponent.h"
#include "P3StatComponent.h"
#include "P3InventoryComponent.h"
#include "P3HPRegen.h"
#include "Kismet/GameplayStatics.h"

UP3HPPotion_Small::UP3HPPotion_Small()
{
	Key = 1;
}

void UP3HPPotion_Small::Use(AP3Character* User)
{	
	Super::Use(User);
	if (User == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HPPotion_Small] : Can't Find Character to use Item."));
		return;
	}

	if (User->GetStatComponent()->GetCurrentHP() == User->GetStatComponent()->GetMaxHP())
	{
		return;
	}

	UP3HPRegen* HPRegenBuff = NewObject<UP3HPRegen>();
	HPRegenBuff->InitBuffData(FString::Printf(TEXT("P3HPPotion's HPRegen")), 5.0f, 50.0f);
	if (User->GetBuffComponent()->ApplyBuff(HPRegenBuff))
	{
		User->GetInventoryComponent()->RemoveItem(this);
	}
}