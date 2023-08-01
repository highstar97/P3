#include "P3Buff.h"

UP3Buff::UP3Buff()
{
	Name = "Buff";
	Duration = -1.0f;
	Image = nullptr;
	Particle = nullptr;
	BuffType = EBuffType::None;
}

UP3Buff::~UP3Buff()
{

}