// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.h"
#include "SignActor.generated.h"


UCLASS()
class UE_RUNNER_API ASignActor : public AActor, public IInteractableObject
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

	UPROPERTY(EditAnywhere, Category = "Interaction")
	FTransform ExclamationSpawnTransform;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	class UUserWidget* SignTextWidget;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	class UTextData* SignTextData;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
		int interactionState = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int Interact();
	virtual int Interact_Implementation() override;

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
