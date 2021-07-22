// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ExclamationPoint.h"
#include "ue_runnerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "TextData.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AArmorerPawn::AArmorerPawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArmorerMesh = CreateDefaultSubobject<UStaticMeshComponent>("SignMesh");
	SetRootComponent(ArmorerMesh);

	InteractionBoundary = CreateDefaultSubobject<USphereComponent>("InteractionBoundary");

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
}

// Called when the game starts or when spawned
void AArmorerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionBoundary->OnComponentBeginOverlap.AddDynamic(this, &AArmorerPawn::OnPlayerOverlapBegin);
	InteractionBoundary->OnComponentEndOverlap.AddDynamic(this, &AArmorerPawn::OnPlayerOverlapEnd);
}

// Called every frame
void AArmorerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArmorerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AArmorerPawn::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UWorld* w = GetWorld();
	APlayerController* pc = UGameplayStatics::GetPlayerController(w, 0);

	if (!OtherActor->IsA(Aue_runnerCharacter::StaticClass())) return;

	isPlayerNearby = true;

	Cast<Aue_runnerCharacter>(OtherActor)->SetInteractable(this);

	FTransform SpawnTransform = ExclamationSpawnTransform;
	SpawnTransform.SetLocation(SpawnTransform.GetLocation() + GetActorTransform().GetLocation());

	FActorSpawnParameters SpawnParams;

	ExclamationPointActor = w->SpawnActor<AExclamationPoint>(ExclamationPoint, SpawnTransform, SpawnParams);
}

void AArmorerPawn::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (!OtherActor->IsA(Aue_runnerCharacter::StaticClass())) return;

	isPlayerNearby = false;

	Cast<Aue_runnerCharacter>(OtherActor)->RemoveInteractable(this);

	ExclamationPointActor->Destroy();

	if (interactionState != 0) {
		interactionState = 0;
		ArmorerWidget->RemoveFromParent();
	}
}

int AArmorerPawn::Interact_Implementation() {
	if (ArmorerWidget == NULL) return 0;

	if (interactionState == 0) {
		interactionState++;
		ArmorerWidget->AddToViewport();
		return interactionState;
	} else {
		interactionState = 0;
		ArmorerWidget->RemoveFromParent();
		return interactionState;
	}
}

