#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3StatComponent.generated.h"

struct FP3CharacterData;

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnExpChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnLevelUpDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3StatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UP3StatComponent() : Level(1), CurrentHP(0.0f), MaxHP(0.0f), CurrentMP(0.0f), MaxMP(0.0f), Attack(0.0f), CurrentExp(0.0f), RequiredExp(0.0f)
	{
		LevelBasedCurrentData = nullptr;
		PrimaryComponentTick.bCanEverTick = false;
	}

	int32 GetLevel() const { return Level; }
	void SetLevel(int32 NewLevel) { this->Level = NewLevel; }

	float GetCurrentHP() const { return CurrentHP; }
	void SetCurrentHP(float NewCurrentHP);

	float GetMaxHP() const { return MaxHP; }
	void SetMaxHP(float NewMaxHP) { this->MaxHP = NewMaxHP; }

	float GetCurrentMP() const { return CurrentMP; }
	void SetCurrentMP(float NewCurrentMP) { this->CurrentMP = NewCurrentMP; }

	float GetMaxMP() const { return MaxMP; }
	void SetMaxMP(float NewMaxMP) { this->MaxMP = NewMaxMP; }

	float GetAttack() const { return Attack; }
	void SetAttack(float NewAttack) { this->Attack = NewAttack; }

	float GetCurrentExp() const { return CurrentExp; }
	void SetCurrentExp(float NewCurrentExp) { this->CurrentExp = NewCurrentExp; }

	float GetRequiredExp() const { return RequiredExp; }
	void SetRequiredExp(float NewRequiredExp) { this->RequiredExp = NewRequiredExp; }

	FP3CharacterData* GetLevelBasedCurrentData() const { return LevelBasedCurrentData; }
	void SetLevelBasedCurrentData(FP3CharacterData* NewLevelBasedData) { this->LevelBasedCurrentData = NewLevelBasedData; }
	
	void LevelUp();
	void ConsumeMP(float UsedMP);
	void AddExp(float GainedExp);
	void TakeDamage(float TakenDamage);

	void SetStatFromDataTable(int32 NewLevel, FP3CharacterData* _LevelBasedData);

	float GetHPRatio() const { return GetCurrentHP() / GetMaxHP(); }
	float GetMPRatio() const { return GetCurrentMP() / GetMaxMP(); }
	float GetExpRatio() const { return GetCurrentExp() / GetRequiredExp(); }

	FOnHPChangedDelegate OnHPChanged;
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnMPChangedDelegate OnMPChanged;
	FOnExpChangedDelegate OnExpChanged;
	FOnLevelUpDelegate OnLevelUp;

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

	FP3CharacterData* LevelBasedCurrentData;
};