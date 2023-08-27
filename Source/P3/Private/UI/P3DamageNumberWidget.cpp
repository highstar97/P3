#include "UI/P3DamageNumberWidget.h"
#include "Components/TextBlock.h"

void UP3DamageNumberWidget::SetDamageNumber(float NewDamageNumber)
{
	Text_DamageNumber->SetText(FText::FromString(FString::SanitizeFloat(NewDamageNumber)));
}