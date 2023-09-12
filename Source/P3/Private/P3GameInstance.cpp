#include "P3GameInstance.h"
#include "P3ItemManager.h"

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

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_HeroSKILL1(TEXT("/Game/GameData/P3HeroSkill1Data.P3HeroSkill1Data"));
	if (DT_HeroSKILL1.Succeeded())
	{
		HeroSkill1DataTable = DT_HeroSKILL1.Object;
		if (HeroSkill1DataTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3GameInstance] No data inside HeroSkill1DataTable."));
		}
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_HeroSKILL2(TEXT("/Game/GameData/P3HeroSkill2Data.P3HeroSkill2Data"));
	if (DT_HeroSKILL2.Succeeded())
	{
		HeroSkill2DataTable = DT_HeroSKILL2.Object;
		if (HeroSkill2DataTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3GameInstance] No data inside HeroSkill2DataTable."));
		}
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_P3Item(TEXT("/Game/GameData/P3ItemData.P3ItemData"));
	if (DT_P3Item.Succeeded())
	{
		P3ItemDataTable = DT_P3Item.Object;
		if (P3ItemDataTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3GameInstance] No data inside P3ItemDataTable."));
		}
	}

	ItemManager = GetItemManager();
	ItemManager->Init(this);
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

FP3SkillData* UP3GameInstance::GetHeroSkill1Data(int32 FromLevel)
{
	return HeroSkill1DataTable->FindRow<FP3SkillData>(*FString::FromInt(FromLevel), TEXT(""));
}

FP3SkillData* UP3GameInstance::GetHeroSkill2Data(int32 FromLevel)
{
	return HeroSkill2DataTable->FindRow<FP3SkillData>(*FString::FromInt(FromLevel), TEXT(""));
}

FP3ItemData* UP3GameInstance::GetP3ItemData(int32 KeyOfItem)
{
	return P3ItemDataTable->FindRow<FP3ItemData>(*FString::FromInt(KeyOfItem), TEXT(""));
}

UP3ItemManager* UP3GameInstance::GetItemManager()
{
	if (!ItemManager)
	{
		ItemManager = NewObject<UP3ItemManager>();
	}
	return ItemManager;
}
