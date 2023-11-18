#pragma once

#include "CoreMinimal.h"
#include "P3Buff.h"
#include "P3HPRegen.generated.h"

UCLASS()
class P3_API UP3HPRegen : public UP3Buff
{
	GENERATED_BODY()
	
public:	
	UP3HPRegen();

	float GetTotalAmount() const { return TotalAmount; }

	void InitBuffData(FString NewName, float NewDuration, float NewTotalAmount);

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		float TotalAmount;
};