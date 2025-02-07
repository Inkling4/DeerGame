// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DeerGameGameMode.generated.h"

UCLASS(minimalapi)
class ADeerGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADeerGameGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Player Login")
	void PostLoginEvent(APlayerController* NewPlayer);
};
