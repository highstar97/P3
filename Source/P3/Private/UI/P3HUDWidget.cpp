#include "P3HUDWidget.h"
#include "P3StatComponent.h"
#include "P3BuffComponent.h"
#include "P3BuffArrayWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UP3HUDWidget::BindCharacterStat(UP3StatComponent* NewStatComponent)
{
	if (NewStatComponent != nullptr)
	{
		CurrentStatComponent = NewStatComponent;
		NewStatComponent->OnHPChanged.AddUObject(this, &UP3HUDWidget::UpdateHUDWidget_HP);
		NewStatComponent->OnShieldChanged.AddUObject(this, &UP3HUDWidget::UpdateHUDWidget_HP);
		NewStatComponent->OnMPChanged.AddUObject(this, &UP3HUDWidget::UpdateHUDWidget_MP);
		NewStatComponent->OnExpChanged.AddUObject(this, &UP3HUDWidget::UpdateHUDWidget_Exp);
	}
}

void UP3HUDWidget::BindCharacterBuff(UP3BuffComponent* NewBuffComponent)
{
	if (NewBuffComponent != nullptr)
	{
		CurrentBuffComponent = NewBuffComponent;
		CurrentBuffComponent->OnBuffStarted.AddUObject(this, &UP3HUDWidget::AddBuff);
		CurrentBuffComponent->OnBuffFinished.AddUObject(this, &UP3HUDWidget::RemoveBuff);
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
	if (CurrentStatComponent.IsValid())
	{
		if (ProgressBar_HP != nullptr)
		{
			ProgressBar_HP->SetPercent(CurrentStatComponent->GetHPRatio());
			Text_CurrentHP->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStatComponent->GetCurrentHP() + CurrentStatComponent->GetShield()))));
			Text_MaxHP->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStatComponent->GetMaxHP()))));
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
	if (CurrentStatComponent.IsValid())
	{
		if (ProgressBar_MP != nullptr)
		{
			ProgressBar_MP->SetPercent(CurrentStatComponent->GetMPRatio());
			Text_CurrentMP->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStatComponent->GetCurrentMP()))));
			Text_MaxMP->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStatComponent->GetMaxMP()))));
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
	if (CurrentStatComponent.IsValid())
	{
		if (ProgressBar_Exp != nullptr)
		{
			ProgressBar_Exp->SetPercent(CurrentStatComponent->GetExpRatio());
			Text_CurrentExp->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStatComponent->GetCurrentExp()))));
			Text_RequiredExp->SetText(FText::FromString(FString::FromInt(FMath::Floor(CurrentStatComponent->GetRequiredExp()))));
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

void UP3HUDWidget::AddBuff(UP3Buff* AddedBuff)
{
	UI_BuffArray->AddBuff(AddedBuff);
}

void UP3HUDWidget::RemoveBuff(UP3Buff* RemovedBuff)
{
	UI_BuffArray->RemoveBuff(RemovedBuff);
}