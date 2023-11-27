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
class UP3SkillComponent;
class UP3WeaponComponent;
class UP3BuffComponent;
class UP3InventoryComponent;
class UP3DamageNumberWidget;
class UInputMappingContext;
class UInputAction;
class UP3Item;

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
	
	UP3StatComponent* GetStatComponent() const { return StatComponent; }
	UP3StateComponent* GetStateComponent() const { return StateComponent; }
	UP3SkillComponent* GetSkillComponent() const { return SkillComponent; }
	UP3WeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
	UP3BuffComponent* GetBuffComponent() const { return BuffComponent; }
	UP3InventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	ECharacterType GetCharacterType() const { return CharacterType; }
	void SetCharacterType(ECharacterType _CharacterType) { CharacterType = _CharacterType; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void Jump() override;
	virtual void StopJumping() override;
	
	virtual void InitStat();
	virtual void InitWeapon();
	virtual void InitSkill();
	virtual void InitItem();

	virtual void Attack();
	virtual void Skill1();
	virtual void Skill2();

	virtual void Die();	

	void LevelUp();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void ShowDamageNumber(float NewDamageNumber);

	void DeleteTimer(FTimerHandle DeleteTimer);

	UFUNCTION(BlueprintCallable)
	void UpdateMaxWalkSpeed(float NewMaxWalkSpeed);

	void HPRegen(float Duration, float TotalAmount, UParticleSystem* NewParticle);
	void MPRegen(float Duration, float TotalAmount, UParticleSystem* NewParticle);

	bool ConsumeMP(float UsedMP);

	UFUNCTION(BlueprintCallable)
	float ApplyDamage(AController* EventInstigator, AP3Character* EventInstigatorActor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		UP3StatComponent* StatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
		UP3StateComponent* StateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
		UP3SkillComponent* SkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		UP3WeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		UP3BuffComponent* BuffComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		UP3InventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* HPBarWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UP3DamageNumberWidget> DamageNumberWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> Skill1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> Skill2Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
		ECharacterType CharacterType = ECharacterType::None;
};