#pragma once

#include "CoreMinimal.h"
#include "P3Character.h"
#include "P3Enemy.generated.h"

class UP3EnemyAnimInstance;

UCLASS()
class P3_API AP3Enemy : public AP3Character
{
	GENERATED_BODY()

public:
	AP3Enemy();

	virtual void InitStat() override;
	virtual void InitWeapon() override;
	virtual void InitSkill() override;
	UFUNCTION(BlueprintCallable)
		virtual void Attack() override;
	virtual void Skill1() override;
	virtual void Die() override;

protected:
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY()
		UP3EnemyAnimInstance* EnemyAnim;
};
