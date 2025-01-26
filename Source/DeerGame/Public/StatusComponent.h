// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEERGAME_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

	float InvulnerableTimer;

public:
	// Sets default values for this component's properties

	UStatusComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int MaxHealth;
	UFUNCTION(BlueprintCallable, Category = "Health")
	int GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(int Damage);
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float InvulnerabilityDuration;
};
