#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "P3HeroController.generated.h"

class UP3HUDWidget;
class UP3InventoryWidget;
class UInputMappingContext;
class UInputAction;

UCLASS()
class P3_API AP3HeroController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AP3HeroController();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* APawn) override;

	void OpenInventory();

	UP3HUDWidget* GetHUDWidget() const { return HUDWidget; }
	UP3InventoryWidget* GetInventoryWidget() const { return InventoryWidget; }

protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UP3HUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UP3InventoryWidget> InventoryWidgetClass;

	UPROPERTY()
		UP3HUDWidget* HUDWidget;

	UPROPERTY()
		UP3InventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> OpenInventoryAction;

	FInputModeGameOnly OnlyGameInputMode;
	FInputModeUIOnly OnlyUIInputMode;
	FInputModeGameAndUI GameAndUIInputMode;
};