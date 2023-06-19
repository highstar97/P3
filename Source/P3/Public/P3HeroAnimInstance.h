#pragma once

#include "CoreMinimal.h"
#include "P3AnimInstance.h"
#include "P3HeroAnimInstance.generated.h"

UCLASS()
class P3_API UP3HeroAnimInstance : public UP3AnimInstance
{
	GENERATED_BODY()
	
public:
	UP3HeroAnimInstance();
	
	virtual void NativeInitializeAnimation() override;
	virtual void PlayAttackMontage() override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage4;
};
