#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3BuffComponent.generated.h"

class UP3Buff;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffStartedDelegate, UP3Buff*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffFinishedDelegate, UP3Buff*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnHealBuffStartedDelegate, float, float, UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnManaRegenBuffStartedDelegate, float, float, UParticleSystem*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3BuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UP3BuffComponent();

	void ApplyBuff(UP3Buff* NewBuff);

	void RemoveBuff(UP3Buff* RemovedBuff);

	FOnBuffStartedDelegate OnBuffStarted;
	FOnBuffFinishedDelegate OnBuffFinished;
	FOnHealBuffStartedDelegate OnHealBuffStarted;
	FOnManaRegenBuffStartedDelegate OnManaRegenBuffStarted;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		TArray<UP3Buff*> Buffs;
};
