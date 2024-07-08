#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnShieldChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnExpChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnLevelUpDelegate);

enum class EBuffOperationTarget : uint8;
enum class EBuffOperationMethod : uint8;
struct FP3CharacterData;
class UP3Buff;

USTRUCT(BlueprintType)
struct FStatByBuffEffect
{
	GENERATED_USTRUCT_BODY()
public:
	FStatByBuffEffect() : AddConstant({}), AddPercent({}), SetConstant({}), SetPercent({}) {};

	UPROPERTY(VisibleInstanceOnly, Category = "Buff | Effect")
	TArray<UP3Buff*> AddConstant;

	UPROPERTY(VisibleInstanceOnly, Category = "Buff | Effect")
	TArray<UP3Buff*> AddPercent;

	UPROPERTY(VisibleInstanceOnly, Category = "Buff | Effect")
	TArray<UP3Buff*> SetConstant;

	UPROPERTY(VisibleInstanceOnly, Category = "Buff | Effect")
	TArray<UP3Buff*> SetPercent;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3StatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UP3StatComponent() : Level(1), CurrentHP(0.0f), Shield(0.0f), MaxHP(0.0f), CurrentMP(0.0f), MaxMP(0.0f), Attack(0.0f), CurrentExp(0.0f), RequiredExp(0.0f)
	{
		PrimaryComponentTick.bCanEverTick = false;

		CharacterDataBasedOnLevel = nullptr;
		IntervalBuffs.Empty();
		DurationBuffs.Empty();
	}

public:
	// Getter
	int32 GetLevel() const { return Level; }

	float GetCurrentHP() const;

	float GetShield() const { return Shield; }

	float GetMaxHP() const { return MaxHP; }

	float GetCurrentMP() const { return CurrentMP; }

	float GetMaxMP() const { return MaxMP; }

	float GetAttack() const { return Attack; }

	float GetCurrentExp() const { return CurrentExp; }

	float GetRequiredExp() const { return RequiredExp; }

	FP3CharacterData* GetCharacterDataBasedOnLevel() const { return CharacterDataBasedOnLevel; }

	float GetHPRatio() const { return (GetCurrentHP() + GetShield()) / GetMaxHP(); }

	float GetMPRatio() const { return GetCurrentMP() / GetMaxMP(); }

	float GetExpRatio() const { return GetCurrentExp() / GetRequiredExp(); }

public:
	// Change ( == Setter)
	void ChangeCharacterDataBasedOnLevel(FP3CharacterData* NewCharacterData);

	void ChangeLevel(const int32 NewLevel);

	void ChangeCurrentHP(const float NewCurrentHP);

	void ChangeShield(const float NewShield);

	void ChangeMaxHP(const float NewMaxHP);

	void ChangeCurrentMP(const float NewCurrentMP);

	void ChangeMaxMP(const float NewMaxMP);

	void ChangeAttack(const float NewAttack);

	void ChangeCurrentExp(const float NewCurrentExp);

	void ChangeRequiredExp(const float NewRequiredExp);

public:
	void UpdateShield();

	void TakeDamage(const float TakenDamage);

	bool ConsumeMP(const float UsedMP);

	void GainExp(const float GainedExp);

	bool IsCurrentHPZero();

// Buff
	void AddBuff(UP3Buff* BuffToAdd);

	void RemoveBuff(UP3Buff* BuffToRemove);

	// Buff removed in the middle.
	void RemoveBuffInTheMiddle(UP3Buff* BuffToRemove);

// Delegate
	FOnHPChangedDelegate OnHPChanged;

	FOnHPIsZeroDelegate OnHPIsZero;

	FOnShieldChangedDelegate OnShieldChanged;

	FOnMPChangedDelegate OnMPChanged;

	FOnExpChangedDelegate OnExpChanged;

	FOnLevelUpDelegate OnLevelUp;

protected:
	virtual void BeginPlay() override;

private:
	void OnUpdateStatBasedOnData();

	float TakeShieldDamage(const float TakenDamage); 
	
	float GetBaseValue(EBuffOperationTarget Base) const;

	void ChangeAddPercentToAddConstant(UP3Buff* Buff);

	void ApplyImmediateBuff(UP3Buff* Buff);

	void ApplyBuffToCurrentHP(EBuffOperationMethod Method, float Constant, float Coefficient, float BaseValue);

	void ApplyBuffToMaxHP(EBuffOperationMethod Method, float Constant, float Coefficient, float BaseValue);

	void ApplyBuffToCurrentMP(EBuffOperationMethod Method, float Constant, float Coefficient, float BaseValue);

	void ApplyBuffToMaxMP(EBuffOperationMethod Method, float Constant, float Coefficient, float BaseValue);

	void ApplyDurationBuff(UP3Buff* Buff);

	void RemoveDurationBuff(UP3Buff* Buff);

	void ApplyIntervalBuff(UP3Buff* Buff);
	
private:
	FP3CharacterData* CharacterDataBasedOnLevel;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	int32 Level;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Health", meta = (AllowPrivateAccess = "true"))
	float CurrentHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Health", meta = (AllowPrivateAccess = "true"))
	float Shield;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Health | Buff", meta = (AllowPrivateAccess = "true"))
	FStatByBuffEffect BuffAboutCurrentHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Health", meta = (AllowPrivateAccess = "true"))
	float MaxHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Health | Buff", meta = (AllowPrivateAccess = "true"))
	FStatByBuffEffect BuffOfMaxHP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Mana", meta = (AllowPrivateAccess = "true"))
	float CurrentMP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Health | Buff", meta = (AllowPrivateAccess = "true"))
	FStatByBuffEffect BuffOfCurrentMP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Mana", meta = (AllowPrivateAccess = "true"))
	float MaxMP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Health | Buff", meta = (AllowPrivateAccess = "true"))
	FStatByBuffEffect BuffOfMaxMP;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	float Attack;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Exp", meta = (AllowPrivateAccess = "true"))
	float CurrentExp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Exp", meta = (AllowPrivateAccess = "true"))
	float RequiredExp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Buff", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UP3Buff>> IntervalBuffs;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stat | Buff", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UP3Buff>> DurationBuffs;
};