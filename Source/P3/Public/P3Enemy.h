#pragma once

#include "CoreMinimal.h"
#include "P3Character.h"
#include "P3Enemy.generated.h"

UCLASS()
class P3_API AP3Enemy : public AP3Character
{
	GENERATED_BODY()

public:
	AP3Enemy();

	virtual void Attack() override;

protected:
	virtual void PostInitializeComponents() override;

/*
public:
	UPROPERTY()
		UP3EnemyAnimInstance* EnemyAnim;
*/
};
