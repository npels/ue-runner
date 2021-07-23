// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "WeaponElementData.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BulletActor.h"
#include "ue_runnerCharacter.h"
#include "ue_runnerGameMode.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("EnemyMesh");
	SetRootComponent(EnemyMesh);
	EnemyMesh->SetMobility(EComponentMobility::Movable);

	PlayerRange = CreateDefaultSubobject<USphereComponent>("InteractionBoundary");

	currentHealth = maxHealth;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRange->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnPlayerOverlapBegin);
	PlayerRange->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnPlayerOverlapEnd);
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

	float damageScale = EnemyElementType->ScaleDamage(damageAmount, elementType);
	float damageTaken = damageAmount * damageScale;

	currentHealth -= damageTaken;
	if (currentHealth <= 0.f) {
		Cast<Aue_runnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->IncrementKills();
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

void AEnemy::PrimaryFire() {
	if (!isPlayerNearby) return;

	UWorld* w = GetWorld();
	ACharacter* pc = UGameplayStatics::GetPlayerCharacter(w, 0);

	FVector attackDirection = pc->GetActorLocation() - GetActorTransform().GetLocation();
	attackDirection.Z = 0;
	attackDirection.Normalize();

	FVector spawnLocation = GetActorLocation() + attackDirection * 100;
	spawnLocation.Z += 50.f;

	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetLocation(spawnLocation);
	SpawnTransform.SetRotation(attackDirection.Rotation().Quaternion());

	FActorSpawnParameters SpawnParams;

	ABulletActor* bulletActor = w->SpawnActor<ABulletActor>(bulletBP, SpawnTransform, SpawnParams);
	bulletActor->SetElementType(currentElement);
	bulletActor->hurtsPlayer = true;

	FTimerHandle attackTimer;
	GetWorldTimerManager().SetTimer(attackTimer, this, &AEnemy::PrimaryFire, attackCooldown);
}

void AEnemy::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!OtherActor->IsA(Aue_runnerCharacter::StaticClass())) return;

	isPlayerNearby = true;

	PrimaryFire();
}

void AEnemy::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (!OtherActor->IsA(Aue_runnerCharacter::StaticClass())) return;

	isPlayerNearby = false;
}
