// Fill out your copyright notice in the Description page of Project Settings.


#include "DeerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ADeerCharacter::ADeerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
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

	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.f, 0.0f);
	GetCharacterMovement()->bIgnoreBaseRotation = true;

	Horns = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Horns"));
	Horns->SetupAttachment(GetMesh(), FName("HornsSocket"));

	HornsBoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Horns BoxCollider"));
	HornsBoxCollider->SetupAttachment(Horns);

	bSpeedBoost = true;

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("Status Component"));

}

// Called when the game starts or when spawned
void ADeerCharacter::BeginPlay()
{
	Super::BeginPlay();
	HornsBoxCollider->Deactivate();
	HornsBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ADeerCharacter::OnBoxBeginOverlap);
}

// Called every frame
void ADeerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(5, 5, FColor::Blue, FString::Printf(TEXT("%f"),GetCharacterMovement()->Velocity.Length()));

}

// Called to bind functionality to input
void ADeerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADeerCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AActor* Actor = OtherActor;
	if (Actor == this)
	{
		return;
	}
	
	if (Actor != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(2, 5, FColor::Yellow, FString("Daddy No"));

	}

	/*if (OtherActor == nullptr)
	{
		Actor = Cast<AActor>(OtherActor);

	}*/

	/*if (Actor == nullptr)
	{

		ADeerCharacter* DeerPlayer = Cast<ADeerCharacter>(Actor);

	}*/


}

void ADeerCharacter::IncreaseSpeed()
{
	
		GetCharacterMovement()->MaxAcceleration = 4048.0;
		GetCharacterMovement()->MaxWalkSpeed = 1000;

		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GEngine->AddOnScreenDebugMessage(5, 5, FColor::Green, FString("hmm"));
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADeerCharacter::DecreaseSpeedOverTime, 3.0f);
		}
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADeerCharacter::DecreaseSpeedOverTime, 3.0f);
	
	



	

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

