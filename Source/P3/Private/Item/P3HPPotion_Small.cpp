#include "P3HPPotion_Small.h"
#include "P3GameInstance.h"
#include "P3Character.h"
#include "P3BuffComponent.h"
#include "P3InventoryComponent.h"
#include "P3Heal.h"
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
	}

	UP3Heal* BuffHeal = NewObject<UP3Heal>();
	BuffHeal->InitHeal(FString::Printf(TEXT("P3HPPotion's Heal")), 5.0f, 50.0f);
	User->GetBuffComponent()->ApplyBuff(BuffHeal);
	User->GetInventoryComponent()->RemoveItem(this);
}