#pragma once

#include "CoreMinimal.h"
#include "P3Buff.h"
#include "P3MPRegen.generated.h"

UCLASS()
class P3_API UP3MPRegen : public UP3Buff
{
	GENERATED_BODY()
	
public:
	UP3MPRegen();

	float GetTotalAmount() const { return TotalAmount; }

	void InitBuffData(FString NewName, float NewDuration, float NewTotalAmount);

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		float TotalAmount;
};