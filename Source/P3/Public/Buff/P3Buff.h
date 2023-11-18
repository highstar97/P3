#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "P3Buff.generated.h"

class UTexture2D;
class UParticleSystem;

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	NONE	UMETA(DisplayName = "None"),
	HPREGEN	UMETA(DisplayName = "HPRegen"),
	MPREGEN	UMETA(DisplayName = "MPRegen"),
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
	UTexture2D* GetImage() const { return Image; }
	UParticleSystem* GetParticle() const { return Particle; }
	EBuffType GetBuffType() const { return BuffType; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		FString Name;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		float Duration;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		UTexture2D* Image;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Buff, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* Particle;

	EBuffType BuffType;
};
