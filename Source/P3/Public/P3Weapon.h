#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "P3Weapon.generated.h"

UCLASS()
class P3_API AP3Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AP3Weapon();

	float GetRaidus() const { return Radius; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		float Radius;
};