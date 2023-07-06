#pragma once

// Is it more effective to manage 'Attack' as a component?

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "P3Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class UP3StatComponent;
class UP3StateComponent;
class UP3WeaponComponent;
class UInputMappingContext;
class UInputAction;
class UP3StatComponent;

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	None	UMETA(DisplayName = "None"),
	Hero	UMETA(DisplayName = "Hero"),
	Enemy	UMETA(DisplayName = "Enemy")
};

UCLASS(config=Game)
class AP3Character : public ACharacter
{
	GENERATED_BODY()

public:
	AP3Character();
	
	UP3StateComponent* GetStateComponent() const { return StateComponent; }
	UP3WeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void Jump() override;
	virtual void StopJumping() override;

	virtual void Attack();
	virtual void Die();

	ECharacterType GetCharacterType() const { return CharacterType; }
	void SetCharacterType(ECharacterType _CharacterType) { CharacterType = _CharacterType; }
	
	void InitStat();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
		void UpdateMaxWalkSpeed(float NewMaxWalkSpeed);
	
	UFUNCTION(BlueprintCallable)
	float ApplyDamage(AController* EventInstigator, AP3Character* EventInstigatorActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		UP3StatComponent* StatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
		UP3StateComponent* StateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		UP3WeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* HPBarWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
		ECharacterType CharacterType = ECharacterType::None;
};