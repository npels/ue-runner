// Fill out your copyright notice in the Description page of Project Settings.


#include "SignActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ExclamationPoint.h"
#include "ue_runnerCharacter.h"

// Sets default values
ASignActor::ASignActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SignMesh = CreateDefaultSubobject<UStaticMeshComponent>("SignMesh");
	SetRootComponent(SignMesh);

	InteractionBoundary = CreateDefaultSubobject<USphereComponent>("InteractionBoundary");
}

// Called when the game starts or when spawned
void ASignActor::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionBoundary->OnComponentBeginOverlap.AddDynamic(this, &ASignActor::OnPlayerOverlapBegin);
	InteractionBoundary->OnComponentEndOverlap.AddDynamic(this, &ASignActor::OnPlayerOverlapEnd);
}

// Called every frame
void ASignActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASignActor::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UWorld* w = GetWorld();
	APlayerController* pc = UGameplayStatics::GetPlayerController(w, 0);

	if (!OtherActor->IsA(Aue_runnerCharacter::StaticClass())) return;

	Cast<Aue_runnerCharacter>(OtherActor)->SetInteractable(this);

	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetLocation(SpawnTransform.GetLocation() + FVector(0.f, 0.f, 100.f));
	SpawnTransform.SetRotation(FQuat());

	FActorSpawnParameters SpawnParams;

	ExclamationPointActor = w->SpawnActor<AExclamationPoint>(ExclamationPoint, SpawnTransform, SpawnParams);
}

void ASignActor::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (!OtherActor->IsA(Aue_runnerCharacter::StaticClass())) return;

	Cast<Aue_runnerCharacter>(OtherActor)->RemoveInteractable(this);

	ExclamationPointActor->Destroy();
}

void ASignActor::Interact() {
	Destroy();
}

