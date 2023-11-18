#include "P3BuffImageWidget.h"
#include "P3Buff.h"
#include "Components/Image.h"

void UP3BuffImageWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UP3Buff* Buff = Cast<UP3Buff>(ListItemObject);
	Image_Buff->SetBrushFromTexture(Buff->GetImage());
}