#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "P3GameInstance.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct FP3CharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FP3CharacterData() : Level(1), MaxHP(1000), MaxMP(700), Attack(50), RequiredExp(100) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float Attack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
		float RequiredExp;
};

UCLASS()
class P3_API UP3GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UP3GameInstance();

	virtual void Init() override;

	FP3CharacterData* GetP3CharacterData(int32 Level);

private:
	UPROPERTY()
		UDataTable* P3CharacterDataTable;
};