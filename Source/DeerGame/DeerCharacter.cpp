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


}

// Called when the game starts or when spawned
void ADeerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADeerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

