#pragma once

#include "CoreMinimal.h"
#include "P3Item.h"
#include "P3MPPotion_Small.generated.h"

UCLASS()
class P3_API UP3MPPotion_Small : public UP3Item
{
	GENERATED_BODY()
	
public:
	UP3MPPotion_Small();

	virtual void Use(AP3Character* User);
};	