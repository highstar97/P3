#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3StateComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3StateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UP3StateComponent() : bIsDead(false), bIsAttacking(false), bIsInAir(false), bIsAccelerating(false), AttackCount(0), Speed(0.0f), Pitch(0.0f), Yaw(0.0f), Roll(0.0f), YawDelta(0.0f), RotationLastTick(FRotator::ZeroRotator)
	{
		PrimaryComponentTick.bCanEverTick = true;
	}

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool GetbIsDead() const { return bIsDead; }
	void SetbIsDead(bool NewbIsDead) { this->bIsDead = NewbIsDead; }

	bool GetbIsAttacking() const { return bIsAttacking; }
	void SetbIsAttacking(bool NewbIsAttacking) { this->bIsAttacking = NewbIsAttacking; }

	bool GetbIsInAir() const { return bIsInAir; }
	void SetbIsInAir(bool NewbIsInAir) { this->bIsInAir = NewbIsInAir; }

	bool GetbIsAccelerating() const { return bIsAccelerating; }
	void SetbIsAccelerating(bool NewbIsAccelerating) { this->bIsAccelerating = NewbIsAccelerating; }

	int32 GetAttackCount() const { return AttackCount; }
	void SetAttackCount(int32 NewAttackCount) { this->AttackCount = NewAttackCount; }

	float GetSpeed() const { return Speed; }
	void SetSpeed(float NewSpeed) { this->Speed = NewSpeed; }

	float GetPitch() const { return Pitch; }
	void SetPitch(float NewPitch) { this->Pitch = NewPitch; }

	float GetYaw() const { return Yaw; }
	void SetYaw(float NewYaw) { this->Yaw = NewYaw; }

	float GetRoll() const { return Roll; }
	void SetRoll(float NewRoll) { this->Roll = NewRoll; }

	float GetYawDelta() const { return YawDelta; }
	void SetYawDelta(float NewYawDelta) { this->YawDelta = NewYawDelta; }

	FRotator GetRotationLastTick() const { return RotationLastTick; }
	void SetRotationLastTick(FRotator NewRotationLastTick) { this->RotationLastTick = NewRotationLastTick; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		bool bIsAccelerating;

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