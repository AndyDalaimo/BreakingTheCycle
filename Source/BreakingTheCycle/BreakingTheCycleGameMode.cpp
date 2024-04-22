// Copyright Epic Games, Inc. All Rights Reserved.

#include "BreakingTheCycleGameMode.h"
#include "BreakingTheCycleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABreakingTheCycleGameMode::ABreakingTheCycleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
