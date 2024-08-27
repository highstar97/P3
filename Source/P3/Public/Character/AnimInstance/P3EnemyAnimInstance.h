#pragma once

#include "CoreMinimal.h"
#include "P3AnimInstance.h"
#include "P3EnemyAnimInstance.generated.h"

UCLASS()
class P3_API UP3EnemyAnimInstance : public UP3AnimInstance
{
	GENERATED_BODY()
	
public:
	UP3EnemyAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void PlayAttackMontage() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage4;
};