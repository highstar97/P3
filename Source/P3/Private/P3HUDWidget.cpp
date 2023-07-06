#include "P3HUDWidget.h"
#include "P3StatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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