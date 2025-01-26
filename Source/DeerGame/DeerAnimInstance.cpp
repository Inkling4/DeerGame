// Fill out your copyright notice in the Description page of Project Settings.


#include "DeerAnimInstance.h"

#include "DeerCharacter.h"
#include "PlayerDeerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UDeerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	if (DeerCharacter == nullptr)
	{
		DeerCharacter = Cast<ADeerCharacter>(TryGetPawnOwner());
	}

	if (DeerCharacter)
	{

		DeerController = Cast<APlayerDeerController>(DeerCharacter->GetController());
		FVector Velocity = DeerCharacter->GetVelocity();
		Velocity.Z = 0.0;
		Speed = Velocity.Size();

		FRotator const AimRotation = DeerCharacter->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(DeerCharacter->GetVelocity());

		bIsFalling = DeerCharacter->GetCharacterMovement()->IsFalling();
		bIsEmote1 = DeerCharacter->bIsEmoting1;
		bIsEmote2 = DeerCharacter->bIsEmoting2;
		bIsEmote3 = DeerCharacter->bIsEmoting3;
		bIsAttacking = DeerCharacter->bIsAttacking;
		
		if (GEngine && bIsEmote1) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("%hs"), bIsEmote1 ? "true" : "false"));
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

	}


}

void UDeerAnimInstance::NativeInitializeAnimation()
{
	if (DeerCharacter == nullptr)
	{
		DeerCharacter = Cast<ADeerCharacter>(TryGetPawnOwner());
	}

	if (DeerCharacter)
	{

		DeerController = Cast<APlayerDeerController>(DeerCharacter->GetController());
		

	}


}
