#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3StatComponent.generated.h"

struct FP3CharacterData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3StatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UP3StatComponent() : Level(1), CurrentHP(0.0f), MaxHP(0.0f), CurrentMP(0.0f), MaxMP(0.0f), Attack(50.0f), CurrentExp(0.0f), RequiredExp(0.0f)
	{
		PrimaryComponentTick.bCanEverTick = false;
	}

	void SetStatFromDataTable(int32 _Level, FP3CharacterData* Data);

	int32 GetLevel() { return Level; }
	void SetLevel(int32 _Level) { this->Level = _Level; }

	float GetCurrentHP() { return CurrentHP; }
	void SetCurrentHP(float _CurrentHP) { this->CurrentHP = _CurrentHP; }

	float GetMaxHP() { return MaxHP; }
	void SetMaxHP(float _MaxHP) { this->MaxHP = _MaxHP; }

	float GetCurrentMP() { return CurrentMP; }
	void SetCurrentMP(float _CurrentMP) { this->CurrentMP = _CurrentMP; }

	float GetMaxMP() { return MaxMP; }
	void SetMaxMP(float _MaxMP) { this->MaxMP = _MaxMP; }

	float GetAttack() { return Attack; }
	void SetAttack(float _Attack) { this->Attack = _Attack; }

	float GetCurrentExp() { return CurrentExp; }
	void SetCurrentExp(float _CurrentExp) { this->CurrentExp = _CurrentExp; }

	float GetRequiredExp() { return RequiredExp; }
	void SetRequiredExp(float _RequiredExp) { this->RequiredExp = _RequiredExp; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		int32 Level;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float CurrentHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float MaxHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float CurrentMP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float MaxMP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float Attack;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float CurrentExp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		float RequiredExp;
};