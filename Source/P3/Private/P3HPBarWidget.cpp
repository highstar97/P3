#include "P3HPBarWidget.h"
#include "P3StatComponent.h"
#include "Components/ProgressBar.h"

void UP3HPBarWidget::BindCharacterStat(UP3StatComponent* NewStat)
{
	if (NewStat != nullptr)
	{
		CurrentStat = NewStat;
		NewStat->OnHPChanged.AddUObject(this, &UP3HPBarWidget::UpdateHPBarWidget);
	}
}

void UP3HPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateHPBarWidget();
}

void UP3HPBarWidget::UpdateHPBarWidget()
{
	if (CurrentStat.IsValid())
	{
		if (ProgressBar_HP != nullptr)
		{
			ProgressBar_HP->SetPercent(CurrentStat->GetHPRatio());
		}
	}
}