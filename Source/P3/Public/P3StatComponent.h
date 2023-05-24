#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P3StatComponent.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
    GENERATED_BODY()

public:
	FStat() : Health(100.0f), Mana(70.0f), Experience(10.0f) {}

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
		float Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
		float Experience;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P3_API UP3StatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UP3StatComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		FStat BasicStat;

	// Used when implementing equipment systems
	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
		FStat EquipmentStat;
	*/
};