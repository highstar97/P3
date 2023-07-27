#include "P3HUDWidget.h"
#include "P3StatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UP3HUDWidget::BindCharacterStat(UP3StatComponent* NewStat)
{
	if (NewStat != nullptr)
	{
		CurrentStat = NewStat;
		NewStat->OnHPChanged.AddUObject(this, &UP3HUDWidget::UpdateHUDWidget_HP);
		NewStat->OnMPChanged.AddUObject(this, &UP3HUDWidget::UpdateHUDWidget_MP);
		NewStat->OnExpChanged.AddUObject(this, &UP3HUDWidget::UpdateHUDWidget_Exp);
	}
}

void UP3HUDWidget::InitHUDWidget(FString NewSkill1Name, FString NewSkill2Name)
{
	if (Text_Skill1 != nullptr)
	{
		Skill1Name = NewSkill1Name;
		Text_Skill1->SetText(FText::FromString(NewSkill1Name));
	}

	if (Text_Skill2 != nullptr)
	{
		Skill2Name = NewSkill2Name;
		Text_Skill2->SetText(FText::FromString(NewSkill2Name));
	}
}
	
void UP3HUDWidget::StartUpdateButtonSkill1(float NewCoolTime)
{
	if (Text_Skill1 != nullptr)
	{
		int32 RemainingTime = FMath::FloorToInt(NewCoolTime);
		Text_Skill1->SetText(FText::FromString(FString::FromInt(RemainingTime)));

		GetWorld()->GetTimerManager().SetTimer(Skill1CoolTimeHandle, [this, RemainingTime, NewCoolTime]()mutable -> void
			{
				if (--RemainingTime > 0)
				{
					Text_Skill1->SetText(FText::FromString(FString::FromInt(RemainingTime)));
				}
				else
				{
					Text_Skill1->SetText(FText::FromString(FString::Printf(TEXT("%s"),*Skill1Name)));
					EndUpdateButtonSkill1();
				}
			}, 1.0f, true);
	}
}

void UP3HUDWidget::StartUpdateButtonSkill2(float NewCoolTime)
{
	if (Text_Skill2 != nullptr)
	{
		int32 RemainingTime = FMath::FloorToInt(NewCoolTime);
		Text_Skill2->SetText(FText::FromString(FString::FromInt(RemainingTime)));

		GetWorld()->GetTimerManager().SetTimer(Skill2CoolTimeHandle, [this, RemainingTime, NewCoolTime]()mutable -> void
			{
				if (--RemainingTime > 0)
				{
					Text_Skill2->SetText(FText::FromString(FString::FromInt(RemainingTime)));
				}
				else
				{
					Text_Skill2->SetText(FText::FromString(FString::Printf(TEXT("%s"), *Skill2Name)));
					EndUpdateButtonSkill2();
				}
			}, 1.0f, true);
	}
}

void UP3HUDWidget::EndUpdateButtonSkill1()
{
	GetWorld()->GetTimerManager().ClearTimer(Skill1CoolTimeHandle);
}

void UP3HUDWidget::EndUpdateButtonSkill2()
{
	GetWorld()->GetTimerManager().ClearTimer(Skill2CoolTimeHandle);
}

void UP3HUDWidget::UpdateHUDWidget_HP()
{
	if (CurrentStat.IsValid())
	{
		if (ProgressBar_HP != nullptr)
		{
			ProgressBar_HP->SetPercent(CurrentStat->GetHPRatio());
			Text_CurrentHP->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStat->GetCurrentHP()))));
			Text_MaxHP->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStat->GetMaxHP()))));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3HUDWidget] Isn't bind on ProgressBar_HP."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HUDWidget] HUDWidget isn't binding with Stat."));
	}
}

void UP3HUDWidget::UpdateHUDWidget_MP()
{
	if (CurrentStat.IsValid())
	{
		if (ProgressBar_MP != nullptr)
		{
			ProgressBar_MP->SetPercent(CurrentStat->GetMPRatio());
			Text_CurrentMP->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStat->GetCurrentMP()))));
			Text_MaxMP->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStat->GetMaxMP()))));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3HUDWidget] Isn't bind on ProgressBar_MP."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HUDWidget] HUDWidget isn't binding with Stat."));
	}
}

void UP3HUDWidget::UpdateHUDWidget_Exp()
{
	if (CurrentStat.IsValid())
	{
		if (ProgressBar_Exp != nullptr)
		{
			ProgressBar_Exp->SetPercent(CurrentStat->GetExpRatio());
			Text_CurrentExp->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStat->GetCurrentExp()))));
			Text_RequiredExp->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStat->GetRequiredExp()))));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3HUDWidget] Isn't bind on ProgressBar_Exp."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3HUDWidget] HUDWidget isn't binding with Stat."));
	}
}