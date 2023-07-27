#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3GameInstance.h"
#include "P3SkillComponent.generated.h"

struct FP3SkillData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3SkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UP3SkillComponent();

	bool GetbIsSkill1Cool() const{ return bIsSkill1Cool; }
	void SetbIsSkill1Cool(bool NewbIsSkill1Cool) { this->bIsSkill1Cool = NewbIsSkill1Cool; }

	bool GetbIsSkill2Cool() const { return bIsSkill2Cool; }
	void SetbIsSkill2Cool(bool NewbIsSkill2Cool) { this->bIsSkill2Cool = NewbIsSkill2Cool; }

	FP3SkillData* GetCurrentSkill1Data() const { return CurrentSkill1Data; }
	void SetCurrentSkill1Data(FP3SkillData* NewSkillData) { this->CurrentSkill1Data = NewSkillData; }

	FP3SkillData* GetCurrentSkill2Data() const { return CurrentSkill2Data; }
	void SetCurrentSkill2Data(FP3SkillData* NewSkillData) { this->CurrentSkill2Data = NewSkillData; }

	int32 GetSkill1Level() const { return CurrentSkill1Data->Level; }
	float GetSkill1NeededMP() const { return CurrentSkill1Data->NeededMP; }
	float GetSkill1CoolTime() const { return CurrentSkill1Data->CoolTime; }

	int32 GetSkill2Level() const { return CurrentSkill2Data->Level; }
	float GetSkill2NeededMP() const { return CurrentSkill2Data->NeededMP; }
	float GetSkill2CoolTime() const { return CurrentSkill2Data->CoolTime; }

	FString GetSkill1Name() const { return Skill1Name; }
	void SetSkill1Name(FString NewSkill1Name) { Skill1Name = NewSkill1Name; }

	FString GetSkill2Name() const { return Skill2Name; }
	void SetSkill2Name(FString NewSkill2Name) { Skill2Name = NewSkill2Name; }

	// Skill LevelUp will be soon...
	// void SkillLevelUp();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
		bool bIsSkill1Cool;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
		bool bIsSkill2Cool;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
		FString Skill1Name;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
		FString Skill2Name;

	FP3SkillData* CurrentSkill1Data;

	FP3SkillData* CurrentSkill2Data;
};