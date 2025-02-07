// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeerGameGameMode.h"
#include "DeerGameCharacter.h"
#include "PlayerDeerController.h"
#include "UObject/ConstructorHelpers.h"

ADeerGameGameMode::ADeerGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADeerGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PostLoginEvent(NewPlayer);
}

void ADeerGameGameMode::PostLoginEvent_Implementation(APlayerController* NewPlayer)
{
	
}
