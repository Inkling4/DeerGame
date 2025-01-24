// Fill out your copyright notice in the Description page of Project Settings.


#include "DeerAnimInstance.h"

#include "DeerCharacter.h"
#include "PlayerDeerController.h"

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
