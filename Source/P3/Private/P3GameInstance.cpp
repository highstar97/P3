#include "P3GameInstance.h"

UP3GameInstance::UP3GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_P3Hero(TEXT("/Game/GameData/P3HeroData.P3HeroData"));
	if (DT_P3Hero.Succeeded())
	{
		P3HeroDataTable = DT_P3Hero.Object;
		if (P3HeroDataTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3GameInstance] No data inside P3HeroDataTable."));
		}
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_P3Enemy(TEXT("/Game/GameData/P3EnemyData.P3EnemyData"));
	if (DT_P3Enemy.Succeeded())
	{
		P3EnemyDataTable = DT_P3Enemy.Object;
		if (P3EnemyDataTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3GameInstance] No data inside P3EnemyDataTable."));
		}
	}
}

void UP3GameInstance::Init()
{
	Super::Init();
}

FP3CharacterData* UP3GameInstance::GetP3HeroData(int32 FromLevel)
{
	return P3HeroDataTable->FindRow<FP3CharacterData>(*FString::FromInt(FromLevel), TEXT(""));
}

FP3EnemyData* UP3GameInstance::GetP3EnemyData(int32 FromLevel)
{
	return P3EnemyDataTable->FindRow<FP3EnemyData>(*FString::FromInt(FromLevel), TEXT(""));
}