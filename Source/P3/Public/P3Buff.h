#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "P3Buff.generated.h"

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	None	UMETA(DisplayName = "None"),
	Heal	UMETA(DisplayName = "Hero"),
	//Speed	UMETA(DisplayName = "Enemy")
};

UCLASS()
class P3_API UP3Buff : public UObject
{
	GENERATED_BODY()
	
public:
	UP3Buff();
	virtual ~UP3Buff();

	FString GetName() const { return Name; }
	float GetDuration() const { return Duration; }
	EBuffType GetBuffType() const { return BuffType; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		FString Name;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		float Duration;

	EBuffType BuffType;
};
