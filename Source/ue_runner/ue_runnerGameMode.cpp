// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue_runnerGameMode.h"
#include "ue_runnerCharacter.h"
#include "ue_runnerPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

Aue_runnerGameMode::Aue_runnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = Aue_runnerPlayerController::StaticClass();
	}
}

void Aue_runnerGameMode::BeginPlay() {

}

void Aue_runnerGameMode::IncrementKills() {
	currentKills++;
	if (currentKills >= killsNeededToWin) {
		UGameplayStatics::OpenLevel(GetWorld(), "Victory");
	}
}
