#include "P3Buff.h"

#include "Particles/ParticleSystem.h"

#include "Character/P3Character.h"
#include "Component/P3StatComponent.h"
#include "Buff/P3BuffManager.h"

void UP3Buff::Apply(AP3Character* Character)
{
	if (TagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName("Stat"))))
	{
		Character->GetStatComponent()->AddBuff(this);
	}
}

void UP3Buff::Remove(AP3Character* Character)
{
	if (TagContainer.HasTag(FGameplayTag::RequestGameplayTag(FName("Stat"))))
	{
		Character->GetStatComponent()->RemoveBuff(this);
	}
}

UP3Buff* UP3Buff::CreateCopy()
{
	UP3Buff* CopiedBuff = NewObject<UP3Buff>(this, UP3Buff::StaticClass());

	CopiedBuff->bIsCopy = true;
	CopiedBuff->Key = this->Key;
	CopiedBuff->Name = "Copy_" + this->Name;
	CopiedBuff->NumericData = this->NumericData;
	CopiedBuff->TagContainer = this->TagContainer;
	CopiedBuff->Image = this->Image;
	CopiedBuff->Particle = this->Particle;

	return CopiedBuff;
}

// must be called in consturctor, because using ConstructorHelpers
void UP3Buff::ConstructBuffFromData(const FP3BuffData* BuffData)
{
	SetKey(BuffData->Key);
	SetbIsCopy(false);
	SetName(BuffData->Name);
	SetNumericData(BuffData->NumericData);
	SetTagContainer(BuffData->TagContainer);
	ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE(*BuffData->TexturePath);
	if (IMAGE.Succeeded())
	{
		SetImage(IMAGE.Object);
	}
	ConstructorHelpers::FObjectFinder<UParticleSystem> PARTICLE(*BuffData->ParticlePath);
	if (PARTICLE.Succeeded())
	{
		SetParticle(PARTICLE.Object);
	}
}