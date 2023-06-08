#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "P3HeroAnimInstance.generated.h"

class AP3Character;

UCLASS()
class P3_API UP3HeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UP3HeroAnimInstance();

	virtual void NativeInitializeAnimation() override;

	void PlayAttackMontage();

private:
	UFUNCTION()
		void AnimNotify_StartAttack();

	UFUNCTION()
		void AnimNotify_SaveAttack();

	UFUNCTION()
		void AnimNotify_EndAttack();

	UFUNCTION()
		void AnimNotify_ResetCombo();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, Meta = (AllowPrivateAccess = "true"))
		AP3Character* P3Character;

	const int32 NumOfAttackMontage = 4;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage4;
};