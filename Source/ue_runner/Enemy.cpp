// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
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

float AEnemy::TakeDamage(float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser) {
	if (beingHurt) return 0.f;

	float damageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	currentHealth -= damageTaken;
	if (currentHealth <= 0.f) {
		Destroy();
		return damageTaken;
	}

	EnemyMesh->SetMaterial(0, HurtMaterial);

	beingHurt = true;
	FTimerHandle HurtTimer;
	GetWorldTimerManager().SetTimer(HurtTimer, this, &AEnemy::StopHurt, 1.0f);

	return damageTaken;
}

void AEnemy::StopHurt() {
	EnemyMesh->SetMaterial(0, DefaultMaterial);
	beingHurt = false;
}

