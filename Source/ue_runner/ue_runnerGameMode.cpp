// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue_runnerGameMode.h"
#include "ue_runnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aue_runnerGameMode::Aue_runnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
