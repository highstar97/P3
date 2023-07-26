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

	FP3SkillData* GetCurrentSkill1Data() const { return CurrentSkill1Data; }
	void SetCurrentSkill1Data(FP3SkillData* NewSkillData) { this->CurrentSkill1Data = NewSkillData; }

	int32 GetSkill1Level() const { return CurrentSkill1Data->Level; }
	float GetSkill1NeededMP() const { return CurrentSkill1Data->NeededMP; }
	float GetSkill1CoolTime() const { return CurrentSkill1Data->CoolTime; }

	FString GetSkill1Name() const { return Skill1Name; }
	void SetSkill1Name(FString NewSkill1Name) { Skill1Name = NewSkill1Name; }

	// Skill LevelUp will be soon...
	// void SkillLevelUp();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
		bool bIsSkill1Cool;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
		FString Skill1Name;

	FP3SkillData* CurrentSkill1Data;
};