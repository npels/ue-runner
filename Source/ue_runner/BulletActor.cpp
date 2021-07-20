// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	SetRootComponent(BulletMesh);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");
	BulletMovement->MaxSpeed = 5000.f;
	BulletMovement->InitialSpeed = 5000.f;
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
	BulletMesh->OnComponentHit.AddDynamic(this, &ABulletActor::OnHit);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor->IsA(AEnemy::StaticClass())) {
		FDamageEvent damageEvent;
		Cast<AEnemy>(OtherActor)->TakeDamage(damage, damageEvent, playerController, this);
	}

	Destroy();
}

