// Fill out your copyright notice in the Description page of Project Settings.


#include "DeerCharacter.h"

#include "PlayerDeerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADeerCharacter::ADeerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 30.f;
	//make player rotate with movement input
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//Player rotation rate

	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->bIgnoreBaseRotation = true;

	Horns = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Horns"));
	Horns->SetupAttachment(GetMesh(), FName("HornsSocket"));

	HornsBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Horns BoxCollider"));
	HornsBoxCollider->SetupAttachment(Horns);
	HornsBoxCollider->SetCollisionProfileName(FName("OverlapAll"));

	bSpeedBoost = true;

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("Status Component"));

	Damage = 5;

	bReplicates = true;
}

void ADeerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADeerCharacter, bIsEmoting1);
	DOREPLIFETIME(ADeerCharacter, bIsEmoting2);
	DOREPLIFETIME(ADeerCharacter, bIsAttacking);
}

// Called when the game starts or when spawned
void ADeerCharacter::BeginPlay()
{
	Super::BeginPlay();
	HornsBoxCollider->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	HornsBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ADeerCharacter::OnBoxBeginOverlap);
}

// Called every frame
void ADeerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(5, 5, FColor::Blue, FString::Printf(TEXT("%f"),GetCharacterMovement()->Velocity.Length()));
	FollowRagDoll(DeltaTime);

}

// Called to bind functionality to input
void ADeerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADeerCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	AActor* Actor = OtherActor;
	if (Actor == this)
	{
		return;
	}
	
	if (Actor != nullptr && Actor->ActorHasTag("Player"))
	{
		
		ADeerCharacter* OtherDeer = Cast<ADeerCharacter>(Actor);
		if (OtherDeer != this)
		{
			if (OtherComp != OtherDeer->HornsBoxCollider)
			{
				GEngine->AddOnScreenDebugMessage(2, 5, FColor::Yellow, FString::Printf(TEXT("%s"), *OtherDeer->GetName()));
				UStatusComponent* StatusComp = OtherDeer->FindComponentByClass<UStatusComponent>();
				if (StatusComp != nullptr)
				{

					StatusComp->TakeDamage(Damage);
				}
			}
			if (OtherComp != OtherDeer->HornsBoxCollider)
			{

				OtherDeer->AttachToComponent(HornsBoxCollider, FAttachmentTransformRules::SnapToTargetIncludingScale);
			}
			
		}


	}
	*/
	
}

void ADeerCharacter::IncreaseSpeed()
{
		GetCharacterMovement()->MaxAcceleration = 3048.0;
		GetCharacterMovement()->MaxWalkSpeed = 1000;

		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GEngine->AddOnScreenDebugMessage(5, 5, FColor::Green, FString("hmm"));
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADeerCharacter::DecreaseSpeedOverTime, 3.0f);
		}
}

void ADeerCharacter::DecreaseSpeedOverTime()
{

	GEngine->AddOnScreenDebugMessage(2, 5, FColor::Red, FString("Decrease speed"));
	float CurrentVelocity = GetCharacterMovement()->MaxWalkSpeed;
	float NewSpeed = FMath::FInterpTo(CurrentVelocity, 600, GetWorld()->GetTimeSeconds(), 250.0f);

	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	if (NewSpeed <= 600)
	{
		GEngine->AddOnScreenDebugMessage(3, 5, FColor::Red, FString("Normal"));
		GetCharacterMovement()->MaxAcceleration = 2048.0;
		GetCharacterMovement()->MaxWalkSpeed = 600;

	}

}

void ADeerCharacter::EnableBoxCollision()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString("On"));
	HornsBoxCollider->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

}

void ADeerCharacter::DisableBoxCollision()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, FString("Off"));
	HornsBoxCollider->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

}

void ADeerCharacter::Emote1_Implementation()
{
	return;
}


void ADeerCharacter::Emote2_Implementation()
{
	return;
}

void ADeerCharacter::Attack_Implementation()
{
	return;
}

void ADeerCharacter::StopAttack_Implementation()
{
	return;
}


void ADeerCharacter::testy()
{
	DecreaseSpeedOverTime();
}

void ADeerCharacter::CPPAttack()
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, FString("Attack"));
		
	if (!bIsAttacking)
	{
		EnableBoxCollision();
		bIsAttacking = true;
		StartDash();
	}
}

void ADeerCharacter::CPPStopAttack()
{
	GEngine->AddOnScreenDebugMessage(3, 5, FColor::Red, FString("StopAttacking"));
	if (bIsAttacking)
	{
		DisableBoxCollision();
		DecreaseSpeedOverTime();
		bIsAttacking = false;

	}

}

void ADeerCharacter::Emote3_Implementation()
{

	return;
}

void ADeerCharacter::RagDoll()
{

	if (bIsRagdoll)
	{
		return;
	}


	if (GetMesh())
	{
		SpringArm->bDoCollisionTest = false;
		GetCapsuleComponent()->Deactivate(),
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
		GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
		bIsRagdoll = true;

	}

	FTimerHandle TimerHandleRagDoll;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleRagDoll, this, &ADeerCharacter::EndRagdoll, 3.0f, false);

}

void ADeerCharacter::FollowRagDoll(float Deltatime)
{

	if (!bIsRagdoll)
	{
		return;
	}
	if (GetMesh())
	{
		if (GetCapsuleComponent())
		{
			GetCapsuleComponent()->SetWorldLocation(GetMesh()->GetSocketLocation(FName("Hip")));

		}

	}

}

void ADeerCharacter::EndRagdoll()
{

	if (!bIsRagdoll)
	{
		return;
	}
	SpringArm->bDoCollisionTest = false;
	GetCapsuleComponent()->Activate();
	GetMesh()->SetSimulatePhysics(false);
	GetMesh()->SetCollisionProfileName(FName("CharacterMesh"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	GetMesh()->SetRelativeLocationAndRotation(FVector(-7.0, 0.0, -90), FRotator(0.0, -90.0, 0.0));
	if (APlayerDeerController* DeerController = Cast<APlayerDeerController>(GetController()))
	{
		DeerController->EndRagdoll();
	}
	

	bIsRagdoll = false;

}

void ADeerCharacter::StartDash_Implementation()
{
	return;
}

void ADeerCharacter::DashLoop_Implementation()
{
	return;
}
