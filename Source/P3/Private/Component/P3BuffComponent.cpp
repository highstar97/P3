#include "P3BuffComponent.h"

#include "P3Character.h"
#include "P3Buff.h"

UP3BuffComponent::UP3BuffComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	ActiveBuffs.Empty();
}

bool UP3BuffComponent::AddBuff(UP3Buff* BuffToAdd)
{
	if(IsValid(BuffToAdd))
	{
		float Duration = BuffToAdd->GetNumericData().Duration;

		BuffToAdd->Apply(OwnerCharacter.Get());
		if (Duration != 0.0f)
		{
			OnBuffStarted.Broadcast(BuffToAdd);
			ActiveBuffs.Emplace(BuffToAdd);

			FTimerHandle BuffTimerHandle;
			FTimerDelegate RemoveBuffDelegate;
			RemoveBuffDelegate.BindUFunction(this, FName("RemoveBuff"), BuffToAdd);

			GetWorld()->GetTimerManager().SetTimer(BuffTimerHandle, RemoveBuffDelegate, Duration, false);
		}
		return true;
	}
	return false;
}

void UP3BuffComponent::RemoveBuff(UP3Buff* BuffToRemove)
{
	int32 Index = ActiveBuffs.IndexOfByKey(BuffToRemove);
	if (Index == INDEX_NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3BuffComponent] Can't find Buff to remove. Buff name : %s"), *BuffToRemove->GetName());
	}

	if (ActiveBuffs.IsValidIndex(Index))
	{
		BuffToRemove->Remove(OwnerCharacter.Get());
		OnBuffFinished.Broadcast(BuffToRemove);
		ActiveBuffs.RemoveAt(Index);
	}
}

void UP3BuffComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AP3Character>(GetOwner());
}