// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponElementData.generated.h"

/**
 * 
 */
UCLASS()
class UE_RUNNER_API UWeaponElementData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FString elementName;

	UPROPERTY(EditAnywhere)
	UWeaponElementData* strength;

	UPROPERTY(EditAnywhere)
	UWeaponElementData* weakness;

	UPROPERTY(EditAnywhere)
	class UMaterial* material;

	float ScaleDamage(float damageAmount, UWeaponElementData* elementType);
};
