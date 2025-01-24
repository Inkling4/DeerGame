// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDeerController.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

APlayerDeerController::APlayerDeerController()
{



}

void APlayerDeerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DeerMappingContext, 0);
	}



}

void APlayerDeerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);



}

void APlayerDeerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerDeerController::Movement);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerDeerController::CameraLook);


	}


}

void APlayerDeerController::Movement(const FInputActionValue& Value)
{

	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, FString("Bitch"));

	FVector2D MoveInput = Value.Get<FVector2D>();

	//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, FString("Bitch"));
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
