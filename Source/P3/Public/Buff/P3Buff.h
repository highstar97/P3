#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "P3Buff.generated.h"

struct FP3BuffData;
class AP3Character;
class UTexture2D;
class UParticleSystem;

UENUM(BlueprintType)
enum class EBuffOperationTarget : uint8
{
	None		UMETA(DisplayName = "None"),
	CurrentHP	UMETA(DisplayName = "CurrentHP"),
	MaxHP		UMETA(DisplayName = "MaxHP"),
	CurrentMP	UMETA(DisplayName = "CurrentMP"),
	MaxMP		UMETA(DisplayName = "MaxMP"),
};

UENUM(BlueprintType)
enum class EBuffOperationMethod : uint8
{
	None		UMETA(DisplayName = "None"),
	AddConstant	UMETA(DisplayName = "AddConstant"),
	AddPercent	UMETA(DisplayName = "AddPercent"),
	SetConstant	UMETA(DisplayName = "SetConstant"),
	SetPercent	UMETA(DisplayName = "SetPercent"),
};

USTRUCT(BlueprintType)
struct FBuffOperationBase
{
	GENERATED_USTRUCT_BODY()
public:
	FBuffOperationBase() : Constant(0.0f), Coefficient(0.0f), Base(EBuffOperationTarget::None) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	float Constant;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	float Coefficient;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	EBuffOperationTarget Base;
};

USTRUCT(BlueprintType)
struct FBuffOperation
{
	GENERATED_USTRUCT_BODY()
public:
	FBuffOperation() : OperationTarget(EBuffOperationTarget::None), OperationMethod(EBuffOperationMethod::None), OperationBase(FBuffOperationBase()) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	EBuffOperationTarget OperationTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	EBuffOperationMethod OperationMethod;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	FBuffOperationBase OperationBase;
};

USTRUCT(BlueprintType)
struct FNumericData
{
	GENERATED_USTRUCT_BODY()
public:
	FNumericData() :Operation(FBuffOperation()), TickInterval(0.0f), Duration(0.0f) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	FBuffOperation Operation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff | Time")
	float TickInterval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff | Time")
	float Duration;
};

UCLASS()
class P3_API UP3Buff : public UObject
{
	GENERATED_BODY()
	
public:
	UP3Buff() : Key(-1), bIsCopy(false), Name("BuffBase"), NumericData(FNumericData()), TagContainer(FGameplayTagContainer::EmptyContainer), Image(nullptr), Particle(nullptr) {};

	void Apply(AP3Character* Character);
	
	void Remove(AP3Character* Character);

	UP3Buff* CreateCopy();

	void ConstructBuffFromData(const FP3BuffData* BuffData);

	FORCEINLINE int32 GetKey() const { return Key; }
	FORCEINLINE void SetKey(const int32 NewKey) { Key = NewKey; }

	FORCEINLINE bool GetbIsCopy() const { return bIsCopy; }
	FORCEINLINE void SetbIsCopy(const bool NewbIsCopy) { bIsCopy = NewbIsCopy; }

	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& NewName) { Name = NewName; }

	FORCEINLINE FNumericData GetNumericData() const { return NumericData; }
	FORCEINLINE void SetNumericData(const FNumericData& NewNumericData) { NumericData = NewNumericData; }
	
	FORCEINLINE FGameplayTagContainer GetTagContainer() const { return TagContainer; }
	FORCEINLINE void SetTagContainer(const FGameplayTagContainer& NewTagContainer) { TagContainer = NewTagContainer; }

	FORCEINLINE UTexture2D* GetImage() const { return Image; }
	FORCEINLINE void SetImage(UTexture2D* NewImage) { Image = NewImage; }

	FORCEINLINE UParticleSystem* GetParticle() const { return Particle; }
	FORCEINLINE void SetParticle(UParticleSystem* NewParticle) { Particle = NewParticle; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	int32 Key;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	bool bIsCopy;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	FNumericData NumericData;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	FGameplayTagContainer TagContainer;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> Image;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> Particle;
};