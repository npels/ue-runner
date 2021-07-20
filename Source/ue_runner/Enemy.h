// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class UE_RUNNER_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* EnemyMesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	class UMaterial* DefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Materials")
	class UMaterial* HurtMaterial;

	UPROPERTY(EditAnywhere, Category = "Health")
	float maxHealth = 3.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float currentHealth;

	bool beingHurt = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	void StopHurt();
};
