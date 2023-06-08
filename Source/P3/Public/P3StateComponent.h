#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3StateComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3StateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UP3StateComponent() : IsAttacking(false), IsInAir(false), IsAccelerating(false), AttackCount(0), Speed(0.0f), Pitch(0.0f), Yaw(0.0f), Roll(0.0f), YawDelta(0.0f), RotationLastTick(FRotator::ZeroRotator)
	{
		PrimaryComponentTick.bCanEverTick = true;
	}

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool GetIsAttacking() const { return IsAttacking; }
	void SetIsAttacking(bool _IsAttacking) { this->IsAttacking = _IsAttacking; }

	bool GetIsInAir() const { return IsInAir; }
	void SetIsInAir(bool _IsInAir) { this->IsInAir = _IsInAir; }

	bool GetIsAccelerating() const { return IsAccelerating; }
	void SetIsAccelerating(bool _IsAccelerating) { this->IsAccelerating = _IsAccelerating; }

	int32 GetAttackCount() const { return AttackCount; }
	void SetAttackCount(int32 _AttackCount) { this->AttackCount = _AttackCount; }

	float GetSpeed() const { return Speed; }
	void SetSpeed(float _Speed) { this->Speed = _Speed; }

	float GetPitch() const { return Pitch; }
	void SetPitch(float _Pitch) { this->Pitch = _Pitch; }

	float GetYaw() const { return Yaw; }
	void SetYaw(float _Yaw) { this->Yaw = _Yaw; }

	float GetRoll() const { return Roll; }
	void SetRoll(float _Roll) { this->Roll = _Roll; }

	float GetYawDelta() const { return YawDelta; }
	void SetYawDelta(float _YawDelta) { this->YawDelta = _YawDelta; }

	FRotator GetRotationLastTick() const { return RotationLastTick; }
	void SetRotationLastTick(FRotator _RotationLastTick) { this->RotationLastTick = _RotationLastTick; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		bool IsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		int32 AttackCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		float Yaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		float Roll;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		float YawDelta;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		FRotator RotationLastTick;
};