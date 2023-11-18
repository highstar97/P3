#pragma once

#include "CoreMinimal.h"
#include "P3Item.h"
#include "P3HPPotion_Small.generated.h"

class AP3Character;

UCLASS()
class P3_API UP3HPPotion_Small : public UP3Item
{
	GENERATED_BODY()
	
public:
	UP3HPPotion_Small();

	virtual void Use(AP3Character* User) override;
};