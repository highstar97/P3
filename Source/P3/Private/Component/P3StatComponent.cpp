#include "P3StatComponent.h"

#include "P3GameInstance.h"
#include "Character/P3Character.h"
#include "Component/P3BuffComponent.h"
#include "Buff/P3Buff.h"

float UP3StatComponent::GetCurrentHP() const
{
	// In preparation for the request ¡°Fix CurrentHP to Y for X seconds || Fix CurrentHP to Z% of Y for X seconds¡±
	if (BuffAboutCurrentHP.SetConstant.IsEmpty() && BuffAboutCurrentHP.SetPercent.IsEmpty())
	{
		return CurrentHP;
	}

	float SetConstant = 0.0f;
	for (UP3Buff* Buff : BuffAboutCurrentHP.SetConstant)
	{
		SetConstant = SetConstant == 0.0f ? Buff->GetNumericData().Operation.OperationBase.Constant : FMath::Min(SetConstant, Buff->GetNumericData().Operation.OperationBase.Constant);
	}

	float SetPercent = 0.0f;
	for (UP3Buff* Buff : BuffAboutCurrentHP.SetPercent)
	{
		const auto& OperationBase = Buff->GetNumericData().Operation.OperationBase;
		float Value = OperationBase.Coefficient * (OperationBase.Base == EBuffOperationTarget::CurrentHP ? CurrentHP : GetBaseValue(OperationBase.Base));
		SetPercent = SetPercent == 0.0f ? Value : FMath::Min(SetPercent, Value);
	}

	return SetPercent == 0.0f ? SetConstant : SetConstant == 0.0f ? SetPercent : FMath::Min(SetConstant, SetPercent);
}

void UP3StatComponent::ChangeCharacterDataBasedOnLevel(FP3CharacterData* NewCharacterData)
{
	CharacterDataBasedOnLevel = NewCharacterData;

	OnUpdateStatBasedOnData();
}

void UP3StatComponent::ChangeLevel(const int32 NewLevel)
{
	this->Level = NewLevel;
}

void UP3StatComponent::ChangeCurrentHP(const float NewCurrentHP)
{
	float ActualChangeValue = FMath::Clamp(NewCurrentHP, 0.0f, GetMaxHP());
	this->CurrentHP = ActualChangeValue;
	OnHPChanged.Broadcast();

	IsCurrentHPZero();
}

void UP3StatComponent::ChangeShield(const float NewShield)
{
	float ActualChangeValue = FMath::Max(0.0f, NewShield);
	this->Shield = NewShield;
	OnShieldChanged.Broadcast();
}

void UP3StatComponent::ChangeMaxHP(const float NewMaxHP)
{
	this->MaxHP = NewMaxHP;
	if (GetCurrentHP() > GetMaxHP())
	{
		ChangeCurrentHP(GetCurrentHP());
	}
}

void UP3StatComponent::ChangeCurrentMP(const float NewCurrentMP)
{
	float ActualChangeValue = FMath::Clamp(NewCurrentMP, 0.0f, GetMaxMP());
	this->CurrentMP = ActualChangeValue;
	OnMPChanged.Broadcast();
}

void UP3StatComponent::ChangeMaxMP(const float NewMaxMP)
{
	this->MaxMP = NewMaxMP;
	if (GetCurrentMP() > GetMaxMP())
	{
		ChangeCurrentMP(GetCurrentMP());
	}
}

void UP3StatComponent::ChangeAttack(const float NewAttack)
{
	this->Attack = NewAttack;
}

void UP3StatComponent::ChangeCurrentExp(const float NewCurrentExp)
{
	this->CurrentExp = NewCurrentExp;
	if(GetCurrentExp() >= GetRequiredExp())
	{
		OnLevelUp.Broadcast();
	}
	OnExpChanged.Broadcast();
}

void UP3StatComponent::ChangeRequiredExp(const float NewRequiredExp)
{
	this->RequiredExp = NewRequiredExp;
	if (GetCurrentExp() >= GetRequiredExp())
	{
		OnLevelUp.Broadcast();
	}
}

void UP3StatComponent::UpdateShield()
{
	float AddedShield = 0.0f;

	for (UP3Buff* Buff : BuffAboutCurrentHP.AddConstant)
	{
		AddedShield += Buff->GetNumericData().Operation.OperationBase.Constant;
	}

	ChangeShield(AddedShield);
}

void UP3StatComponent::TakeDamage(const float TakenDamage)
{
	// Calculate at Shield first	
	if (GetShield() > 0.0f)
	{
		float RestDamage = TakeShieldDamage(TakenDamage);
		// if RestDamage, Calculate at CurrentHP
		if (RestDamage < 0.0f)
		{
			ChangeCurrentHP(GetCurrentHP() + RestDamage);
		}
	}
	else
	{
		ChangeCurrentHP(GetCurrentHP() - TakenDamage);
	}
}

bool UP3StatComponent::ConsumeMP(const float UsedMP)
{
	float RemainingMP = GetCurrentMP() - UsedMP;
	if (RemainingMP < 0.0f) return false;
	
	ChangeCurrentMP(RemainingMP);
	return true;
}

void UP3StatComponent::GainExp(const float GainedExp)
{
	ChangeCurrentExp(GetCurrentExp() + GainedExp);
}

bool UP3StatComponent::IsCurrentHPZero()
{
	if (GetCurrentHP() < KINDA_SMALL_NUMBER)
	{
		this->CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
		return true;
	}
	return false;
}

void UP3StatComponent::AddBuff(UP3Buff* BuffToAdd)
{
	FNumericData NumericData = BuffToAdd->GetNumericData();
	FBuffOperation BuffOperation = NumericData.Operation;
	float Duration = NumericData.Duration;
	float TickInterval = NumericData.TickInterval;
	
	if (Duration == 0.0f)
	{
		ApplyImmediateBuff(BuffToAdd);
		return;
	}
	
	if (TickInterval == 0.0f)
	{
		ApplyDurationBuff(BuffToAdd);
		DurationBuffs.Emplace(BuffToAdd);
	}
	else
	{
		ApplyIntervalBuff(BuffToAdd);
		IntervalBuffs.Emplace(BuffToAdd);
	}
}

void UP3StatComponent::RemoveBuff(UP3Buff* BuffToRemove)
{
	if (BuffToRemove->GetNumericData().TickInterval == 0.0f)
	{
		RemoveDurationBuff(BuffToRemove);
		DurationBuffs.Remove(BuffToRemove);
	}
	else
	{
		IntervalBuffs.Remove(BuffToRemove);
	}
}

void UP3StatComponent::RemoveBuffInTheMiddle(UP3Buff* BuffToRemove)
{
	Cast<AP3Character>(GetOwner())->GetBuffComponent()->RemoveBuff(BuffToRemove);
}

void UP3StatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UP3StatComponent::OnUpdateStatBasedOnData()
{
	ChangeMaxHP(CharacterDataBasedOnLevel->MaxHP);
	ChangeCurrentHP(GetMaxHP());
	ChangeMaxMP(CharacterDataBasedOnLevel->MaxMP);
	ChangeCurrentMP(GetMaxMP());
	ChangeAttack(CharacterDataBasedOnLevel->Attack);
	ChangeRequiredExp(CharacterDataBasedOnLevel->RequiredExp);
	OnExpChanged.Broadcast();
}

float UP3StatComponent::TakeShieldDamage(const float TakenDamage)
{
	float InitShield = GetShield();
	float Damage = TakenDamage;
	// Shield processing order is constant -> percent
	for (UP3Buff* Buff : BuffAboutCurrentHP.AddConstant)
	{
		if (Buff->GetNumericData().Operation.OperationBase.Constant <= Damage)
		{
			Damage -= Buff->GetNumericData().Operation.OperationBase.Constant;
			ChangeShield(GetShield() - Buff->GetNumericData().Operation.OperationBase.Constant);
			RemoveBuffInTheMiddle(Buff);
		}
		else
		{
			FNumericData NewNumericData = Buff->GetNumericData();
			NewNumericData.Operation.OperationBase.Constant -= Damage;
			Buff->SetNumericData(NewNumericData);
			ChangeShield(GetShield() - Damage);
			return InitShield - TakenDamage;
		}
	}
	return InitShield - TakenDamage;
}

float UP3StatComponent::GetBaseValue(EBuffOperationTarget Base) const
{
	switch (Base)
	{
	case EBuffOperationTarget::CurrentHP:
		return GetCurrentHP();
	case EBuffOperationTarget::MaxHP:
		return GetMaxHP();
	case EBuffOperationTarget::CurrentMP:
		return GetCurrentMP();
	case EBuffOperationTarget::MaxMP:
		return GetMaxMP();
	default:
		return 0.0f;
	}
}

void UP3StatComponent::ChangeAddPercentToAddConstant(UP3Buff* Buff)
{
	FNumericData NewNumericData = Buff->GetNumericData();
	NewNumericData.Operation.OperationMethod = EBuffOperationMethod::AddConstant;
	NewNumericData.Operation.OperationBase.Constant = NewNumericData.Operation.OperationBase.Coefficient * GetBaseValue(NewNumericData.Operation.OperationBase.Base);
	NewNumericData.Operation.OperationBase.Coefficient = 0.0f;
	NewNumericData.Operation.OperationBase.Base = EBuffOperationTarget::None;
	Buff->SetNumericData(NewNumericData);
}

void UP3StatComponent::ApplyImmediateBuff(UP3Buff* Buff)
{
	FBuffOperation BuffOperation = Buff->GetNumericData().Operation;
	EBuffOperationTarget Target = BuffOperation.OperationTarget;
	EBuffOperationMethod Method = BuffOperation.OperationMethod;
	float Constant = BuffOperation.OperationBase.Constant;
	float Coefficient = BuffOperation.OperationBase.Coefficient;
	float BaseValue = GetBaseValue(BuffOperation.OperationBase.Base);

	switch (Target)
	{
	case EBuffOperationTarget::CurrentHP:
		ApplyBuffToCurrentHP(Method, Constant, Coefficient, BaseValue);
		break;
	case EBuffOperationTarget::MaxHP:
		ApplyBuffToMaxHP(Method, Constant, Coefficient, BaseValue);
		break;
	case EBuffOperationTarget::CurrentMP:
		ApplyBuffToCurrentMP(Method, Constant, Coefficient, BaseValue);
		break;
	case EBuffOperationTarget::MaxMP:
		ApplyBuffToMaxMP(Method, Constant, Coefficient, BaseValue);
		break;
	}
}

void UP3StatComponent::ApplyBuffToCurrentHP(EBuffOperationMethod Method, float Constant, float Coefficient, float BaseValue)
{
	switch (Method)
	{
	case EBuffOperationMethod::AddConstant:
		ChangeCurrentHP(GetCurrentHP() + Constant);
		break;
	case EBuffOperationMethod::AddPercent:
		ChangeCurrentHP(GetCurrentHP() + Coefficient * BaseValue);
		break;
	case EBuffOperationMethod::SetConstant:
		ChangeCurrentHP(Constant);
		break;
	case EBuffOperationMethod::SetPercent:
		ChangeCurrentHP(Coefficient * BaseValue);
		break;
	}
}

void UP3StatComponent::ApplyBuffToMaxHP(EBuffOperationMethod Method, float Constant, float Coefficient, float BaseValue)
{
	switch (Method)
	{
	case EBuffOperationMethod::AddConstant:
		ChangeMaxHP(GetMaxHP() + Constant);
		break;
	case EBuffOperationMethod::AddPercent:
		ChangeMaxHP(GetMaxHP() + Coefficient * BaseValue);
		break;
	case EBuffOperationMethod::SetConstant:
		ChangeMaxHP(Constant);
		break;
	case EBuffOperationMethod::SetPercent:
		ChangeMaxHP(Coefficient * BaseValue);
		break;
	}
}

void UP3StatComponent::ApplyBuffToCurrentMP(EBuffOperationMethod Method, float Constant, float Coefficient, float BaseValue)
{
	switch (Method)
	{
	case EBuffOperationMethod::AddConstant:
		ChangeCurrentMP(GetCurrentMP() + Constant);
		break;
	case EBuffOperationMethod::AddPercent:
		ChangeCurrentMP(GetCurrentMP() + Coefficient * BaseValue);
		break;
	case EBuffOperationMethod::SetConstant:
		ChangeCurrentMP(Constant);
		break;
	case EBuffOperationMethod::SetPercent:
		ChangeCurrentMP(Coefficient * BaseValue);
		break;
	}
}

void UP3StatComponent::ApplyBuffToMaxMP(EBuffOperationMethod Method, float Constant, float Coefficient, float BaseValue)
{
	switch (Method)
	{
	case EBuffOperationMethod::AddConstant:
		ChangeMaxMP(GetMaxMP() + Constant);
		break;
	case EBuffOperationMethod::AddPercent:
		ChangeMaxMP(GetMaxMP() + Coefficient * BaseValue);
		break;
	case EBuffOperationMethod::SetConstant:
		ChangeMaxMP(Constant);
		break;
	case EBuffOperationMethod::SetPercent:
		ChangeMaxMP(Coefficient * BaseValue);
		break;
	}
}

void UP3StatComponent::ApplyDurationBuff(UP3Buff* Buff)
{
	FBuffOperation BuffOperation = Buff->GetNumericData().Operation;
	EBuffOperationTarget Target = BuffOperation.OperationTarget;
	EBuffOperationMethod Method = BuffOperation.OperationMethod;

	switch (Target)
	{
	case EBuffOperationTarget::CurrentHP:
		switch (Method)
		{
		case EBuffOperationMethod::AddConstant:
			BuffAboutCurrentHP.AddConstant.Emplace(Buff);
			UpdateShield();
			break;
		case EBuffOperationMethod::AddPercent:
			ChangeAddPercentToAddConstant(Buff);
			BuffAboutCurrentHP.AddConstant.Emplace(Buff);
			UpdateShield();
			break;
		case EBuffOperationMethod::SetConstant:
			BuffAboutCurrentHP.SetConstant.Emplace(Buff);
			break;
		case EBuffOperationMethod::SetPercent:
			BuffAboutCurrentHP.SetPercent.Emplace(Buff);
			break;
		}
		OnHPChanged.Broadcast();
		break;
	case EBuffOperationTarget::MaxHP:
		switch (Method)
		{
		case EBuffOperationMethod::AddConstant:
			BuffOfMaxHP.AddConstant.Emplace(Buff);
			break;
		case EBuffOperationMethod::AddPercent:
			BuffOfMaxHP.AddPercent.Emplace(Buff);
			break;
		case EBuffOperationMethod::SetConstant:
			BuffOfMaxHP.SetConstant.Emplace(Buff);
			break;
		case EBuffOperationMethod::SetPercent:
			BuffOfMaxHP.SetPercent.Emplace(Buff);
			break;
		}
		OnHPChanged.Broadcast();
		break;
	case EBuffOperationTarget::CurrentMP:
		switch (Method)
		{
		case EBuffOperationMethod::AddConstant:
			BuffOfCurrentMP.AddConstant.Emplace(Buff);
			break;
		case EBuffOperationMethod::AddPercent:
			BuffOfCurrentMP.AddPercent.Emplace(Buff);
			break;
		case EBuffOperationMethod::SetConstant:
			BuffOfCurrentMP.SetConstant.Emplace(Buff);
			break;
		case EBuffOperationMethod::SetPercent:
			BuffOfCurrentMP.SetPercent.Emplace(Buff);
			break;
		}
		OnMPChanged.Broadcast();
		break;
	case EBuffOperationTarget::MaxMP:
		switch (Method)
		{
		case EBuffOperationMethod::AddConstant:
			BuffOfMaxMP.AddConstant.Emplace(Buff);
			break;
		case EBuffOperationMethod::AddPercent:
			BuffOfMaxMP.AddPercent.Emplace(Buff);
			break;
		case EBuffOperationMethod::SetConstant:
			BuffOfMaxMP.SetConstant.Emplace(Buff);
			break;
		case EBuffOperationMethod::SetPercent:
			BuffOfMaxMP.SetPercent.Emplace(Buff);
			break;
		}
		OnMPChanged.Broadcast();
		break;
	}
}

void UP3StatComponent::RemoveDurationBuff(UP3Buff* Buff)
{
	FBuffOperation BuffOperation = Buff->GetNumericData().Operation;
	EBuffOperationTarget Target = BuffOperation.OperationTarget;
	EBuffOperationMethod Method = BuffOperation.OperationMethod;

	switch (Target)
	{
	case EBuffOperationTarget::CurrentHP:
		switch (Method)
		{
		case EBuffOperationMethod::AddConstant:
			BuffAboutCurrentHP.AddConstant.RemoveSingle(Buff);
			UpdateShield();
			break;
		case EBuffOperationMethod::AddPercent:
			BuffAboutCurrentHP.AddConstant.RemoveSingle(Buff);
			UpdateShield();
			break;
		case EBuffOperationMethod::SetConstant:
			BuffAboutCurrentHP.SetConstant.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::SetPercent:
			BuffAboutCurrentHP.SetPercent.RemoveSingle(Buff);
			break;
		}
		OnHPChanged.Broadcast();
		break;
	case EBuffOperationTarget::MaxHP:
		switch (Method)
		{
		case EBuffOperationMethod::AddConstant:
			BuffOfMaxHP.AddConstant.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::AddPercent:
			BuffOfMaxHP.AddPercent.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::SetConstant:
			BuffOfMaxHP.SetConstant.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::SetPercent:
			BuffOfMaxHP.SetPercent.RemoveSingle(Buff);
			break;
		}
		OnHPChanged.Broadcast();
		break;
	case EBuffOperationTarget::CurrentMP:
		switch (Method)
		{
		case EBuffOperationMethod::AddConstant:
			BuffOfCurrentMP.AddConstant.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::AddPercent:
			BuffOfCurrentMP.AddPercent.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::SetConstant:
			BuffOfCurrentMP.SetConstant.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::SetPercent:
			BuffOfCurrentMP.SetPercent.RemoveSingle(Buff);
			break;
		}
		OnMPChanged.Broadcast();
		break;
	case EBuffOperationTarget::MaxMP:
		switch (Method)
		{
		case EBuffOperationMethod::AddConstant:
			BuffOfMaxMP.AddConstant.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::AddPercent:
			BuffOfMaxMP.AddPercent.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::SetConstant:
			BuffOfMaxMP.SetConstant.RemoveSingle(Buff);
			break;
		case EBuffOperationMethod::SetPercent:
			BuffOfMaxMP.SetPercent.RemoveSingle(Buff);
			break;
		}
		OnMPChanged.Broadcast();
		break;
	}
}

void UP3StatComponent::ApplyIntervalBuff(UP3Buff* Buff)
{
	FNumericData NumericData = Buff->GetNumericData();
	float Duration = NumericData.Duration;
	float TickInterval = NumericData.TickInterval;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, Buff]()
		{
			ApplyImmediateBuff(Buff);
		}), TickInterval, true);

	FTimerHandle EndTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(EndTimerHandle, FTimerDelegate::CreateLambda([this, Buff, &TimerHandle]()
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			RemoveBuff(Buff);
		}), Duration, false);
}