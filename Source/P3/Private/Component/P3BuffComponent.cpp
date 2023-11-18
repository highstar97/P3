#include "P3BuffComponent.h"
#include "P3Buff.h"
#include "P3HPRegen.h"
#include "P3MPRegen.h"
#include "P3Character.h"

UP3BuffComponent::UP3BuffComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Buffs.Empty();
}

/*
	When On__BuffStarted Broadcast, Character do __.
*/
void UP3BuffComponent::ExecuteHPRegenEffect(UP3Buff* HPRegenBuff)
{
	float Duration = HPRegenBuff->GetDuration();
	float TotalAmount = Cast<UP3HPRegen>(HPRegenBuff)->GetTotalAmount();
	UParticleSystem* Particle = HPRegenBuff->GetParticle();

	OnHPRegenBuffStarted.Broadcast(Duration, TotalAmount, Particle);
	OnBuffStarted.Broadcast(HPRegenBuff);
}

void UP3BuffComponent::ExecuteMPRegenEffect(UP3Buff* MPRegenBuff)
{
	float Duration = MPRegenBuff->GetDuration();
	float TotalAmount = Cast<UP3MPRegen>(MPRegenBuff)->GetTotalAmount();
	UParticleSystem* Particle = MPRegenBuff->GetParticle();

	OnMPRegenBuffStarted.Broadcast(Duration, TotalAmount, Particle);
	OnBuffStarted.Broadcast(MPRegenBuff);
}

void UP3BuffComponent::StartBuffTimer(UP3Buff* Buff)
{
	FTimerHandle RemoveBuffTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(RemoveBuffTimerHandle, FTimerDelegate::CreateLambda([this, Buff]()->void {
		RemoveBuff(Buff);
		}), Buff->GetDuration(), false);
}

bool UP3BuffComponent::IsBuffDuplicated(UP3Buff* BuffBeCheckedDuplication)
{
	for (UP3Buff* Buff : Buffs)
	{
		if (Buff->GetName() == BuffBeCheckedDuplication->GetName())
		{
			return true;
		}
	}
	return false;
}

bool UP3BuffComponent::ApplyBuff(UP3Buff* NewBuff)
{
	if (IsBuffDuplicated(NewBuff))
	{
		// When Buff is Duplicated, Can't Use.
		return false;
	}

	Buffs.Emplace(NewBuff);

	switch (NewBuff->GetBuffType())
	{
	case(EBuffType::NONE):
	{
		break;
	}
	case(EBuffType::HPREGEN):
	{
		ExecuteHPRegenEffect(NewBuff);
		break;
	}
	case(EBuffType::MPREGEN):
	{
		ExecuteMPRegenEffect(NewBuff);
		break;
	}
	default:
		UE_LOG(LogTemp, Warning, TEXT("[P3BuffComponent] : BuffType is unknown."));
		break;
	}
	StartBuffTimer(NewBuff);
	return true;
}

bool UP3BuffComponent::RemoveBuff(UP3Buff* RemovedBuff)
{
	if (Buffs.Find(RemovedBuff) != INDEX_NONE)
	{
		Buffs.Remove(RemovedBuff);
		OnBuffFinished.Broadcast(RemovedBuff);
		return true;
	}
	return false;
}

void UP3BuffComponent::BeginPlay()
{
	Super::BeginPlay();
}