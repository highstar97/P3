#pragma once

#include "CoreMinimal.h"
#include "P3Character.h"
#include "P3Hero.generated.h"

class UP3HeroAnimInstance;

UCLASS()
class P3_API AP3Hero : public AP3Character
{
	GENERATED_BODY()
	
public:
	AP3Hero();

	virtual void Attack() override;

protected:
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY()
		UP3HeroAnimInstance* HeroAnim;
};
