#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "P3EnemyController.generated.h"

class UBehaviorTree;
class UBlackboardData;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class P3_API AP3EnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AP3EnemyController();

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* APawn) override;

private:
	UPROPERTY(VisibleAnywhere, Category = AI)
		TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;

	TObjectPtr<UAISenseConfig_Sight> AISenseConfigSight = nullptr;

	UPROPERTY()
		UBehaviorTree* BTAsset;

	UPROPERTY()
		UBlackboardData* BBAsset;
};
