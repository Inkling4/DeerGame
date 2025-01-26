// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "StatusComponent.h"
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Horns")
	int Damage;


	bool bSpeedBoost;
	FTimerHandle TimerHandle;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void IncreaseSpeed();

	UFUNCTION()
	void DecreaseSpeedOverTime();



	//Attack box Colliderstuff

	UFUNCTION()
	void EnableBoxCollision();

	UFUNCTION()
	void DisableBoxCollision();

	//Attack functions
	void testy();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void CPPAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void CPPStopAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	UStatusComponent* StatusComponent;

	UFUNCTION(BlueprintNativeEvent, Category = "Emotes")
	void Emote1();

	UFUNCTION(BlueprintNativeEvent, Category = "Emotes")
	void Emote2();
	UFUNCTION(BlueprintNativeEvent, Category = "Emotes")
	void Emote3();

	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	void Attack();

	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	void StartDash();

	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	void DashLoop();

	UFUNCTION(BlueprintNativeEvent, Category = "Attack")
	void StopAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotes", Replicated)
	bool bIsEmoting1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotes", Replicated)
	bool bIsEmoting2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotes", Replicated)
	bool bIsEmoting3;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emotes", Replicated)
	bool bIsAttacking;


	//RagDoll
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsRagdoll;


	UFUNCTION(BlueprintCallable)
	void RagDoll();

	void FollowRagDoll(float Deltatime);

	void EndRagdoll();


};
