// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDeerController.h"

#include "AudioDevice.h"
#include "DeerCharacter.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Net/UnrealNetwork.h"

APlayerDeerController::APlayerDeerController()
{

	bIsAttacking = false;
	bIsRagdoll = false;
}

void APlayerDeerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DeerMappingContext, 0);
	}

	//ProfileName = GetCharacter()->GetMesh()->GetCollisionProfileName();

	if (DeerCharacter == nullptr)
	{
		DeerCharacter = Cast<ADeerCharacter>(GetCharacter());
	}

}

void APlayerDeerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//FollowRagDoll(DeltaSeconds);

	
	
}

void APlayerDeerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerDeerController::Movement);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerDeerController::CameraLook);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerDeerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerDeerController::StopJump);
		EnhancedInputComponent->BindAction(RagDollAction, ETriggerEvent::Triggered, this, &APlayerDeerController::RagDoll);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerDeerController::Attack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &APlayerDeerController::StopAttack);
		EnhancedInputComponent->BindAction(Emote1Action, ETriggerEvent::Triggered, this, &APlayerDeerController::Emote1);
		EnhancedInputComponent->BindAction(Emote2Action, ETriggerEvent::Triggered, this, &APlayerDeerController::Emote2);
		EnhancedInputComponent->BindAction(Emote3Action, ETriggerEvent::Triggered, this, &APlayerDeerController::Emote3);

	}


}

void APlayerDeerController::Movement(const FInputActionValue& Value)
{

	//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, FString("Bitch"));

	FVector2D MoveInput = Value.Get<FVector2D>();

	
	if (GetCharacter() != nullptr)
	{
		const FRotator YawPlayerRotation = FRotator(0, GetControlRotation().Yaw, 0);

		const FVector ForwardBackwards = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::Y);

		const FVector RightDirection = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::X);

		GetPawn()->AddMovementInput(ForwardBackwards, MoveInput.X);
		GetPawn()->AddMovementInput(RightDirection, MoveInput.Y);

	}


}

void APlayerDeerController::CameraLook(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();


	if (GetCharacter() != nullptr)
	{

		GetCharacter()->AddControllerYawInput(LookInput.X);
		GetCharacter()->AddControllerPitchInput(LookInput.Y);

	}



}

void APlayerDeerController::Jump()
{
	GetCharacter()->Jump();

}

void APlayerDeerController::StopJump()
{
	GetCharacter()->StopJumping();

}

void APlayerDeerController::UseAbility()
{




}

void APlayerDeerController::RagDoll()
{
	if (bIsRagdoll)
	{
		return;
	}

	SetIgnoreMoveInput(true);
	if (IsValid(DeerCharacter))
	{
		DeerCharacter->RagDoll();

	}
	bIsRagdoll = true;
}
//
//void APlayerDeerController::FollowRagDoll(float Deltatime)
//{
//	if (!bIsRagdoll)
//	{
//		return;
//	}
//	if (USkeletalMeshComponent* Mesh = GetCharacter()->GetMesh())
//	{
//		if (UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(GetCharacter()->GetCapsuleComponent()) )
//		{
//			Capsule->SetWorldLocation(Mesh->GetSocketLocation(FName("Hip")));
//
//		}
//
//	}
//
//
//}

void APlayerDeerController::EndRagdoll()
{
	if (!bIsRagdoll)
	{
		return;
	}

	
	if (IsValid(DeerCharacter))
	{
		SetIgnoreMoveInput(false);
		
	}
	bIsRagdoll = false;

}

void APlayerDeerController::Emote1()
{
	if (IsValid(DeerCharacter))
	{
		DeerCharacter->Emote1();
	}
}


void APlayerDeerController::Emote2()
{
	if (IsValid(DeerCharacter))
	{
		DeerCharacter->Emote2();
	}
}

void APlayerDeerController::Emote3()
{
	if (IsValid(DeerCharacter))
	{
		DeerCharacter->Emote3();
	}

}

void APlayerDeerController::Attack()
{
	if (IsValid(DeerCharacter))
	{
		DeerCharacter->Attack();
	}
}

void APlayerDeerController::StopAttack()
{
	if (IsValid(DeerCharacter))
	{
		DeerCharacter->StopAttack();
	}
}
