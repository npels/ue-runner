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

	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* PlayerRange;

	UPROPERTY(EditAnywhere, Category = "Materials")
	class UMaterial* DefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Materials")
	class UMaterial* WeakHurtMaterial;

	UPROPERTY(EditAnywhere, Category = "Materials")
	class UMaterial* NormalHurtMaterial;

	UPROPERTY(EditAnywhere, Category = "Materials")
	class UMaterial* StrongHurtMaterial;

	UPROPERTY(EditAnywhere, Category = "Health")
	float maxHealth = 3.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float currentHealth;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	float damageCooldown = 0.15f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float attackCooldown = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UWeaponElementData* EnemyElementType;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AActor> bulletBP;

	UPROPERTY(EditAnywhere, Category = "Attack")
	class UWeaponElementData* currentElement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
	bool isPlayerNearby = false;

	bool beingHurt = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeElementalDamage(float damageAmount, class UWeaponElementData* elementType);

	void StopHurt();

	void PrimaryFire();
	void PrimaryFireEpilogue();

private:
	UFUNCTION()
	void OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
