// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "DeerCharacter.generated.h"

UCLASS()
class DEERGAME_API ADeerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADeerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraArm")
	class USpringArmComponent* SpringArm;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Horns")
	class UStaticMeshComponent* Horns;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Horns")
	class UBoxComponent* HornsBoxCollider;

	bool bSpeedBoost;
	FTimerHandle TimerHandle;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void IncreaseSpeed();

	UFUNCTION()
	void DecreaseSpeedOverTime();


};
