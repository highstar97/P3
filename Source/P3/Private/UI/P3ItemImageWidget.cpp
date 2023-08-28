#include "P3ItemImageWidget.h"
#include "P3Item.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UP3ItemImageWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UP3Item* Item = dynamic_cast<UP3Item*>(ListItemObject);
	Image_Item->SetBrushFromTexture(Item->GetImage());
	//Text_NumOfItems->SetText(TEXT("1");
}