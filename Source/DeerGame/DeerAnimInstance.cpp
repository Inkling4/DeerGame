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

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if (DeerController)
		{
			bIsAttacking = DeerController->bIsAttacking;
		}

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
