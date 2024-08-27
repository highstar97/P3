#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "P3Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;
class UP3StatComponent;
class UP3StateComponent;
class UP3SkillComponent;
class UP3WeaponComponent;
class UP3BuffComponent;
class UParticleSystemComponent;
class UP3InventoryComponent;
class UWidgetComponent;
class UP3DamageNumberWidget;
class UInputMappingContext;
class UInputAction;

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
	
public:
	UP3StatComponent* GetStatComponent() const { return StatComponent; }

	UP3StateComponent* GetStateComponent() const { return StateComponent; }

	UP3SkillComponent* GetSkillComponent() const { return SkillComponent; }

	UP3WeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

	UP3BuffComponent* GetBuffComponent() const { return BuffComponent; }

	UP3InventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	ECharacterType GetCharacterType() const { return CharacterType; }

	void SetCharacterType(ECharacterType NewCharacterType) { CharacterType = NewCharacterType; }

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual void Jump() override;

	virtual void StopJumping() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
protected:
	virtual void InitStat();

	virtual void InitWeapon();

	virtual void InitSkill();

	virtual void InitItem();

	virtual void Attack(); // ToDo : Is it more effective to manage 'Attack' as a component?

	virtual void Skill1();

	virtual void Skill2();

	virtual void Die();	

protected:
	void LevelUp();

	bool ConsumeMP(const float InitialUsedMP);

	UFUNCTION(BlueprintCallable)
	float ApplyDamage(AController* EventInstigator, AP3Character* EventInstigatorActor);

private:
	void ShowDamageNumber(float NewDamageNumber);

private:
	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UP3StatComponent> StatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UP3StateComponent> StateComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UP3SkillComponent> SkillComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UP3WeaponComponent> WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UP3BuffComponent> BuffComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UP3InventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> HPBarWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	ECharacterType CharacterType = ECharacterType::None;

	// Damage Widget
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UP3DamageNumberWidget> DamageNumberWidgetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<UP3DamageNumberWidget>> DamageNumberWidgetArray;

	int32 DamageNumberWidgetIndex;
	
	// InputAction 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Skill1Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Skill2Action;
};