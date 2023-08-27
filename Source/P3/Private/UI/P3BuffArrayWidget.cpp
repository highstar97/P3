#include "P3BuffArrayWidget.h"
#include "P3Buff.h"
#include "Components/TileView.h"

void UP3BuffArrayWidget::AddBuff(UP3Buff* AddedBuff)
{
	Tile_Buffs->AddItem(AddedBuff);
}

void UP3BuffArrayWidget::DeleteBuff(UP3Buff* DeletedBuff)
{
	Tile_Buffs->RemoveItem(DeletedBuff);
}
