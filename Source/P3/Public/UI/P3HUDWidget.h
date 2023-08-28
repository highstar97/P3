#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "P3HUDWidget.generated.h"

class UP3StatComponent;
class UP3BuffComponent;
class UP3Buff;
class UP3BuffArrayWidget;
class UProgressBar;
class UTextBlock;
class UButton;

UCLASS()
class P3_API UP3HUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(UP3StatComponent* NewStatComponent);
	void BindCharacterBuff(UP3BuffComponent* NewBuffComponent);

	void InitHUDWidget(FString NewSkill1Name, FString NewSkill2Name);

	void SetEnableButtonSkill1(bool NewbEnableButton) { Button_Skill1->SetIsEnabled(NewbEnableButton); }
	void SetEnableButtonSkill2(bool NewbEnableButton) { Button_Skill2->SetIsEnabled(NewbEnableButton); }

	void StartUpdateButtonSkill1(float NewCoolTime);
	void StartUpdateButtonSkill2(float NewCoolTime);

	void EndUpdateButtonSkill1();
	void EndUpdateButtonSkill2();

protected:
	void UpdateHUDWidget_HP();
	void UpdateHUDWidget_MP();
	void UpdateHUDWidget_Exp();

	void AddBuff(UP3Buff* AddedBuff);
	void RemoveBuff(UP3Buff* RemovedBuff);

private:
	TWeakObjectPtr<UP3StatComponent> CurrentStatComponent = nullptr;

	TWeakObjectPtr<UP3BuffComponent> CurrentBuffComponent = nullptr;

	UPROPERTY(meta = (BindWidget))
		UP3BuffArrayWidget* UI_BuffArray;

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

	UPROPERTY(meta = (BindWidget))
		UButton* Button_Skill1;

	UPROPERTY(meta = (BindWidget))
		UButton* Button_Skill2;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Skill1;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Text_Skill2;

	FString Skill1Name;

	FString Skill2Name;

	FTimerHandle Skill1CoolTimeHandle;

	FTimerHandle Skill2CoolTimeHandle;
};
