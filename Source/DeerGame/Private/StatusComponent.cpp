// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Health = 0;
	MaxHealth = 0;
	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	// ...
	
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

int UStatusComponent::GetHealth() const //Returns the current health of actor as an int
{
	return Health;
}

void UStatusComponent::TakeDamage(int Damage) //Actor loses health equal to input parameter (int)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString("ouch"));
	if (bIsInvincible )
	{
		return;
	}

	if (InvulnerableTimer > 0)
	{
		InvulnerableTimer -= GetWorld()->GetTimeSeconds();

		return;
	}
	
	Health -= Damage/4;

	InvulnerableTimer = InvulnerabilityDuration;
	
	if (Health < 0)
	{
		Health = 0;
	}
}
