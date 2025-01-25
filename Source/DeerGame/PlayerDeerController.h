// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "PlayerDeerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;

UCLASS()
class DEERGAME_API APlayerDeerController : public APlayerController
{
	GENERATED_BODY()

public:

	APlayerDeerController();

protected:


	virtual void BeginPlay() override;


	virtual  void Tick(float DeltaSeconds) override;


	virtual void SetupInputComponent() override;

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputMapping")
	UInputMappingContext* DeerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	UInputAction* AbilityAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	UInputAction* RagDollAction;

	//Move function
	UFUNCTION(BlueprintCallable)
	void Movement(const FInputActionValue& Value);

	//Camera
	UFUNCTION(BlueprintCallable)
	void CameraLook(const FInputActionValue& Value);


	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void StopJump();


	//Attack

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bIsAttacking;


	UFUNCTION(BlueprintCallable)
	void Attack();



	//Use Ability
	UFUNCTION(BlueprintCallable)
	void UseAbility();

	

	//Ragdoll
	UPROPERTY()
	FName ProfileName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsRagdoll;

	UFUNCTION(BlueprintCallable)
	void RagDoll();

	void FollowRagDoll(float Deltatime);

	void EndRagdoll();

	
};
