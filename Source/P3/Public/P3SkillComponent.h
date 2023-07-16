#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "P3SkillComponent.generated.h"

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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3SkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UP3SkillComponent();

	bool GetbIsSkill1Cool() const{ return bIsSkill1Cool; }
	void SetbIsSkill1Cool(bool NewbIsSkill1Cool) { this->bIsSkill1Cool = NewbIsSkill1Cool; }

	UDataTable* GetSkill1DataTable() const { return Skill1DataTable; }
	void SetSkill1DataTable(UDataTable* NewSkill1DataTable) { this->Skill1DataTable = NewSkill1DataTable; }

	FP3SkillData* GetSkill1DataFromTable(int32 FromLevel);
	void SetSkill1DataFromLevel(int32 FromLevel);

	int32 GetSkill1Level() const { return Skill1Data->Level; }
	float GetSkill1NeededMP() const { return Skill1Data->NeededMP; }
	float GetSkill1CoolTime() const { return Skill1Data->CoolTime; }

	// Skill LevelUp will be soon...
	// void SkillLevelUp();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
		bool bIsSkill1Cool;

	UPROPERTY()
		UDataTable* Skill1DataTable;

	FP3SkillData* Skill1Data;
};