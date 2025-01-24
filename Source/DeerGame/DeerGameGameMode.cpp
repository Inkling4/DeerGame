// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeerGameGameMode.h"
#include "DeerGameCharacter.h"
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
