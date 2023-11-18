#pragma once

#include "CoreMinimal.h"
#include "P3Buff.h"
#include "P3Heal.generated.h"

UCLASS()
class P3_API UP3Heal : public UP3Buff
{
	GENERATED_BODY()
	
public:	
	UP3Heal();

	float GetTotalHealAmount() const { return TotalHealAmount; }

	void InitHeal(FString NewName, float NewDuration, float NewTotalHealAmount);

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		float TotalHealAmount;
};