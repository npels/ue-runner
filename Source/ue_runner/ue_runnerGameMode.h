// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ue_runnerGameMode.generated.h"

UCLASS(minimalapi)
class Aue_runnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	Aue_runnerGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};



