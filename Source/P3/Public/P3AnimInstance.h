#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "P3AnimInstance.generated.h"

class AP3Character;

UCLASS()
class P3_API UP3AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UP3AnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void PlayAttackMontage();

protected:
	UFUNCTION()
		virtual void AnimNotify_StartAttack();

	UFUNCTION()
		virtual void AnimNotify_SaveAttack();

	UFUNCTION()
		virtual void AnimNotify_EndAttack();

	UFUNCTION()
		virtual void AnimNotify_ResetCombo();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, Meta = (AllowPrivateAccess = "true"))
		AP3Character* P3Character;

	const int32 NumOfAttackMontage = 4;
};