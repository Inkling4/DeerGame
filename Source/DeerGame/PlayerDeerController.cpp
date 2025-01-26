// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDeerController.h"

#include "AssetTypeCategories.h"
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

	FollowRagDoll(DeltaSeconds);

	
	
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

void APlayerDeerController::testy()
{
	DeerCharacter->DecreaseSpeedOverTime();
}

void APlayerDeerController::Attack()
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, FString("Attack"));

	//bIsAttacking = true;

	
	
	
	if (!bIsAttacking)
	{
		DeerCharacter->EnableBoxCollision();
		bIsAttacking = true;
		DeerCharacter->IncreaseSpeed();
		FTimerHandle Time;
		GetWorld()->GetTimerManager().SetTimer(Time, this, &APlayerDeerController::testy, 3.0, false);
	}
	
	


}

void APlayerDeerController::StopAttack()
{
	GEngine->AddOnScreenDebugMessage(3, 5, FColor::Red, FString("StopAttacking"));
	if (bIsAttacking)
	{
		DeerCharacter->DisableBoxCollision();
		DeerCharacter->DecreaseSpeedOverTime();
		bIsAttacking = false;

	}

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
	
	
	if (USkeletalMeshComponent* Mesh = GetCharacter()->GetMesh())
	{
		Mesh->SetCollisionProfileName(FName("Ragdoll"));
		Mesh->SetSimulatePhysics(true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
		GetCharacter()->GetCapsuleComponent()->Deactivate();
		bIsRagdoll = true;

	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this, &APlayerDeerController::EndRagdoll, 3.0f, false);

}

void APlayerDeerController::FollowRagDoll(float Deltatime)
{
	if (!bIsRagdoll)
	{
		return;
	}
	if (USkeletalMeshComponent* Mesh = GetCharacter()->GetMesh())
	{
		if (UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(GetCharacter()->GetCapsuleComponent()) )
		{
			Capsule->SetWorldLocation(Mesh->GetSocketLocation(FName("Hip")));

		}

	}


}

void APlayerDeerController::EndRagdoll()
{
	if (!bIsRagdoll)
	{
		return;
	}

	SetIgnoreMoveInput(false);
	if (USkeletalMeshComponent* Mesh = GetCharacter()->GetMesh())
	{
		GetCharacter()->GetCapsuleComponent()->Activate();
		Mesh->SetSimulatePhysics(false);
		Mesh->SetCollisionProfileName(FName("CharacterMesh"));
		Mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		GetCharacter()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->AttachToComponent(GetCharacter()->GetCapsuleComponent(),FAttachmentTransformRules::SnapToTargetIncludingScale);
		Mesh->SetRelativeLocationAndRotation(FVector(-7.0, 0.0, -90), FRotator(0.0, -90.0, 0.0));
		
		bIsRagdoll = false;

	}


}

void APlayerDeerController::Emote1_Implementation()
{
	bIsEmoting1 = true;

	if (HasAuthority())
	{
		RPC_Server_Emote1();

		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Emote Auth"));
	}

	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Emote Client"));

		RPC_Server_Emote1();
	}
}

bool APlayerDeerController::RPC_Server_Emote1_Validate()
{
	return true;
}

void APlayerDeerController::RPC_Server_Emote1_Implementation()
{
	bIsEmoting1 = true;

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Emote Server"));
}

void APlayerDeerController::EndEmote1()
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, FString("Bitch"));
	bIsEmoting1 = false;
}

void APlayerDeerController::Emote2()
{
	bIsEmoting2 = true;
}

void APlayerDeerController::EndEmote2()
{

	bIsEmoting2 = false;
}
