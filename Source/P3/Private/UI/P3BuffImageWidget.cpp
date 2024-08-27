#include "P3BuffImageWidget.h"

#include "Components/Image.h"

#include "P3Buff.h"

void UP3BuffImageWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UP3Buff* Buff = Cast<UP3Buff>(ListItemObject);
	
	Image_Buff->SetBrushFromTexture(Buff->GetImage());
	Image_Buff->SetToolTipText(FText::FromString(Buff->GetName()));
}