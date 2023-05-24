#include "P3GameInstance.h"

UP3GameInstance::UP3GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_P3CHARACTER(TEXT("/Game/GameData/P3CharacterData.P3CharacterData"));
	if (DT_P3CHARACTER.Succeeded())
	{
		P3CharacterDataTable = DT_P3CHARACTER.Object;
		if (P3CharacterDataTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("[P3GameInstance] P3CharacterDataTable 내부에 Data가 없습니다."));
		}
	}
}

void UP3GameInstance::Init()
{
	Super::Init();
}

FP3CharacterData* UP3GameInstance::GetP3CharacterData(int32 Level)
{
	return P3CharacterDataTable->FindRow<FP3CharacterData>(*FString::FromInt(Level), TEXT(""));
}