#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3WeaponComponent.generated.h"

class AP3Weapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UP3WeaponComponent();

	void EquipWeapon(AP3Weapon* NewWeapon);
	void HideWeapon(bool NewHidden);
	void DestroyWeapon();

	UFUNCTION(BlueprintCallable)
		float GetWeaponRadius() const;

	AP3Weapon* SpawnBasicSword();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AP3Weapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		AP3Weapon* Weapon;
};
