#pragma once

#include "CoreMinimal.h"
#include "P3Character.h"
#include "P3Hero.generated.h"

class UP3HeroAnimInstance;

UCLASS()
class P3_API AP3Hero : public AP3Character
{
	GENERATED_BODY()
	
public:
	AP3Hero();

	virtual void Attack() override;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY()
		UP3HeroAnimInstance* HeroAnim;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;
};