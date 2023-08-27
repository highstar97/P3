#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "P3HPBarWidget.generated.h"

class UP3StatComponent;
class UProgressBar;

UCLASS()
class P3_API UP3HPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(UP3StatComponent* NewStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPBarWidget();

private:
	TWeakObjectPtr<UP3StatComponent> CurrentStat = nullptr;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* ProgressBar_HP;
};