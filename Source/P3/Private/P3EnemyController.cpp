#include "P3EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AP3EnemyController::AP3EnemyController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");

	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB_ENEMY(TEXT("/Game/AI/BB_Enemy.BB_Enemy"));
	if (BB_ENEMY.Succeeded())
	{
		BBAsset = BB_ENEMY.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_ENEMY(TEXT("/Game/AI/BT_Enemy.BT_Enemy"));
	if (BT_ENEMY.Succeeded())
	{
		BTAsset = BT_ENEMY.Object;
	}
}

void AP3EnemyController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AP3EnemyController::OnPossess(APawn* APawn)
{
	Super::OnPossess(APawn);
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3EnemyController] Can't Run Behavior Tree."));
		}
	}
	this->Blackboard = BlackboardComp;
}