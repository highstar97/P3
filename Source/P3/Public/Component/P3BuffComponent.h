#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3BuffComponent.generated.h"

class AP3Character;
class UP3Buff;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffStartedDelegate, UP3Buff*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffFinishedDelegate, UP3Buff*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3BuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UP3BuffComponent();
	
	bool AddBuff(UP3Buff* BuffToAdd);

	UFUNCTION()
	void RemoveBuff(UP3Buff* BuffToRemove);

public:
	FOnBuffStartedDelegate OnBuffStarted;

	FOnBuffFinishedDelegate OnBuffFinished;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Buff | Owner")
	TWeakObjectPtr<AP3Character> OwnerCharacter;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UP3Buff>> ActiveBuffs;
};