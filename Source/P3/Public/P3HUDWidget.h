#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3HUDWidget.generated.h"

class UP3StatComponent;
class UProgressBar;
class UTextBlock;

UCLASS()
class P3_API UP3HUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(UP3StatComponent* NewStat);

protected:
	void UpdateHUDWidget_HP();
	void UpdateHUDWidget_MP();
	void UpdateHUDWidget_Exp();

private:
	TWeakObjectPtr<UP3StatComponent> CurrentStat = nullptr;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* ProgressBar_HP;
	
	UPROPERTY(meta = (BindWidget))
		UProgressBar* ProgressBar_MP;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* ProgressBar_Exp;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_CurrentHP;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_MaxHP;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_CurrentMP;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_MaxMP;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_CurrentExp;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_RequiredExp;
};
