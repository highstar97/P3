#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3BuffComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnHealBuffStartedDelegate, float, float, UParticleSystem*);

class UP3Buff;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3BuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UP3BuffComponent();

	void ApplyBuff(UP3Buff* NewBuff);

	void DeleteBuff(UP3Buff* DeletedBuff);

	FOnHealBuffStartedDelegate OnHealBuffStarted;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		TArray<UP3Buff*> Buffs;
};
