#include "P3MPPotion_Small.h"
#include "P3GameInstance.h"
#include "P3Character.h"
#include "P3BuffComponent.h"
#include "P3InventoryComponent.h"
#include "P3ManaRegen.h"
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
	}

	UP3ManaRegen* BuffManaRegen = NewObject<UP3ManaRegen>();
	BuffManaRegen->InitManaRegen(FString::Printf(TEXT("P3MPPotion's ManaRegen")), 5.0f, 50.0f);
	User->GetBuffComponent()->ApplyBuff(BuffManaRegen);
	User->GetInventoryComponent()->RemoveItem(this);
}