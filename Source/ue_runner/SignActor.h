// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.h"
#include "SignActor.generated.h"


UCLASS()
class UE_RUNNER_API ASignActor : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignActor();

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* SignMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* InteractionBoundary;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	TSubclassOf<class AExclamationPoint> ExclamationPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact() override;

	class AExclamationPoint* ExclamationPointActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
