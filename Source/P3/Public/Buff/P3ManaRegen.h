#pragma once

#include "CoreMinimal.h"
#include "P3Buff.h"
#include "P3ManaRegen.generated.h"

UCLASS()
class P3_API UP3ManaRegen : public UP3Buff
{
	GENERATED_BODY()
	
public:
	UP3ManaRegen();

	float GetTotalManaRegenAmount() const { return TotalManaRegenAmount; }

	void InitManaRegen(FString NewName, float NewDuration, float NewTotaManaRegenAmount);

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		float TotalManaRegenAmount;
};