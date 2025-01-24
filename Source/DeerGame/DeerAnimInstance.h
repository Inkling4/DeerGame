// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DeerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEERGAME_API UDeerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class ADeerCharacter* DeerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class APlayerDeerController* DeerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;


};
