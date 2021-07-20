// Fill out your copyright notice in the Description page of Project Settings.


#include "ExclamationPoint.h"

// Sets default values
AExclamationPoint::AExclamationPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExclamationPointMesh = CreateDefaultSubobject<UStaticMeshComponent>("ExclamationPointMesh");
	SetRootComponent(ExclamationPointMesh);
	ExclamationPointMesh->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AExclamationPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExclamationPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

