// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "WeaponElementData.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("EnemyMesh");
	SetRootComponent(EnemyMesh);
	EnemyMesh->SetMobility(EComponentMobility::Movable);

	currentHealth = maxHealth;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeElementalDamage(float damageAmount, class UWeaponElementData* elementType) {
	if (beingHurt) return 0.f;

	float damageScale = elementType->ScaleDamage(damageAmount, elementType);
	float damageTaken = damageAmount * damageScale;

	currentHealth -= damageTaken;
	if (currentHealth <= 0.f) {
		Destroy();
		return damageTaken;
	}

	if (damageScale > 1) {
		EnemyMesh->SetMaterial(0, StrongHurtMaterial);
	} else if (damageScale < 1) {
		EnemyMesh->SetMaterial(0, WeakHurtMaterial);
	} else {
		EnemyMesh->SetMaterial(0, NormalHurtMaterial);
	}
	

	beingHurt = true;
	FTimerHandle HurtTimer;
	GetWorldTimerManager().SetTimer(HurtTimer, this, &AEnemy::StopHurt, damageCooldown);

	return damageTaken;
}

void AEnemy::StopHurt() {
	EnemyMesh->SetMaterial(0, DefaultMaterial);
	beingHurt = false;
}

