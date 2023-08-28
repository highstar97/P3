#include "P3BuffComponent.h"
#include "P3Buff.h"
#include "P3Heal.h"
#include "P3Character.h"

UP3BuffComponent::UP3BuffComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Buffs.Empty();
}

void UP3BuffComponent::ApplyBuff(UP3Buff* NewBuff)
{
	// After Checking Same Buff. if Duplicated, Clear past buff and start new buff.
	for (UP3Buff* Buff : Buffs)
	{
		if (Buff == NewBuff)
		{
			RemoveBuff(Buff);
			break;
		}
	}
	Buffs.Emplace(NewBuff);

	// Buff Separation -> Correct Delegate Execution?
	switch (NewBuff->GetBuffType())
	{
	case(EBuffType::None):
	{
		break;
	}
	case(EBuffType::Heal):
	{
		float Duration = NewBuff->GetDuration();
		float TotalHealAmount = dynamic_cast<UP3Heal*>(NewBuff)->GetTotalHealAmount();
		UParticleSystem* Particle = NewBuff->GetParticle();
		OnHealBuffStarted.Broadcast(Duration, TotalHealAmount, Particle);
		OnBuffStarted.Broadcast(NewBuff);
		FTimerHandle DeleteBuffTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(DeleteBuffTimerHandle, FTimerDelegate::CreateLambda([this, NewBuff]()->void {
			RemoveBuff(NewBuff);
			}), Duration, false);
		break;
	}
	default:
		break;
	}
}

void UP3BuffComponent::RemoveBuff(UP3Buff* RemovedBuff)
{
	Buffs.Remove(RemovedBuff);
	OnBuffFinished.Broadcast(RemovedBuff);
}

void UP3BuffComponent::BeginPlay()
{
	Super::BeginPlay();
}