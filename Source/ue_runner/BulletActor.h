// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class UE_RUNNER_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UProjectileMovementComponent* BulletMovement;

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
	float damage = 1.f;

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
	class UWeaponElementData* currentElement;

	bool hurtsPlayer = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetElementType(class UWeaponElementData* element);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
