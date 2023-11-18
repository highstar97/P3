#include "P3MPPotion_Small.h"
#include "P3GameInstance.h"
#include "P3Character.h"
#include "P3BuffComponent.h"
#include "P3StatComponent.h"
#include "P3InventoryComponent.h"
#include "P3MPRegen.h"
#include "Kismet/GameplayStatics.h"

UP3MPPotion_Small::UP3MPPotion_Small()
{
	Key = 2;
}

void UP3MPPotion_Small::Use(AP3Character* User)
{
	Super::Use(User);
	if (User == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3MPPotion_Small] : Can't Find Character to use Item."));
		return;
	}

	if (User->GetStatComponent()->GetCurrentMP() == User->GetStatComponent()->GetMaxMP())
	{
		return;
	}

	UP3MPRegen* MPRegenBuff = NewObject<UP3MPRegen>();
	MPRegenBuff->InitBuffData(FString::Printf(TEXT("P3MPPotion's MPRegen")), 5.0f, 50.0f);
	if (User->GetBuffComponent()->ApplyBuff(MPRegenBuff))
	{
		User->GetInventoryComponent()->RemoveItem(this);
	}
}