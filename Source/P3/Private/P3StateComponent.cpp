#include "P3StateComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UP3StateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	APawn* Pawn = Cast<APawn>(GetOwner());

	if (::IsValid(Pawn))
	{
		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
		bIsAccelerating = Cast<ACharacter>(Pawn)->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.0f ? true : false;
		Speed = Pawn->GetVelocity().Length();
		FRotator DeltaRotator = (Pawn->GetBaseAimRotation() - Pawn->GetActorRotation());
		Pitch = DeltaRotator.Pitch;
		Yaw = DeltaRotator.Yaw;
		Roll = DeltaRotator.Roll;
		RotationLastTick = Pawn->GetActorRotation();
		YawDelta = FMath::FInterpTo(YawDelta, (((RotationLastTick - Pawn->GetActorRotation()).Yaw / DeltaTime) / 7.0f), DeltaTime, 6.0f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[P3StateComponent] Can't Cast AActor to Pawn."));
	}
}

void UP3StateComponent::BeginPlay()
{
	Super::BeginPlay();
}