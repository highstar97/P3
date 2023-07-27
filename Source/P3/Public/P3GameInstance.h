#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "P3GameInstance.generated.h"

class UDataTable;

// FP3CharacterData is used for Hero, but since it serves as the parent of Enemy, Character name is used instead of Hero to clarify the inheritance structure.
USTRUCT(BlueprintType)
struct FP3CharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FP3CharacterData() : Level(1), MaxHP(3000.0f), MaxMP(2000.0f), Attack(150.0f), RequiredExp(100) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float RequiredExp;
};

USTRUCT(BlueprintType)
struct FP3EnemyData : public FP3CharacterData
{
	GENERATED_BODY()

public:
	FP3EnemyData() : DropExp(20.0f) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float DropExp;
};

USTRUCT(BlueprintType)
struct FP3SkillData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FP3SkillData() : Level(1), NeededMP(10.0f), CoolTime(1.0f) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float NeededMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float CoolTime;
};

UCLASS()
class P3_API UP3GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UP3GameInstance();

	virtual void Init() override;

	FP3CharacterData* GetP3HeroData(int32 FromLevel);
	FP3EnemyData* GetP3EnemyData(int32 FromLevel);
	FP3SkillData* GetHeroSkill1Data(int32 FromLevel);
	FP3SkillData* GetHeroSkill2Data(int32 FromLevel);

private:
	UPROPERTY()
		UDataTable* P3HeroDataTable;

	UPROPERTY()
		UDataTable* P3EnemyDataTable;

	UPROPERTY()
		UDataTable* HeroSkill1DataTable;

	UPROPERTY()
		UDataTable* HeroSkill2DataTable;
};