#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3DamageNumberWidget.generated.h"

class UTextBlock;

UCLASS()
class P3_API UP3DamageNumberWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDamageNumber(float NewDamageNumber);

private:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_DamageNumber;
};