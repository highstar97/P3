#pragma once

#include "CoreMinimal.h"
#include "P3Buff.h"
#include "P3HPRegen.generated.h"

UCLASS()
class P3_API UP3HPRegen : public UP3Buff
{
	GENERATED_BODY()
	
public:	
	UP3HPRegen();

	virtual void Apply(AP3Character* Character) override;

	virtual void Remove(AP3Character* Character) override;
};