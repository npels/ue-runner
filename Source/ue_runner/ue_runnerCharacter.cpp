// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue_runnerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "BulletActor.h"
#include "InteractableActor.h"

//////////////////////////////////////////////////////////////////////////
// Aue_runnerCharacter

Aue_runnerCharacter::Aue_runnerCharacter() {

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.0f; // The camera follows at this distance behind the character	

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void Aue_runnerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	// Set up gameplay key bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &Aue_runnerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &Aue_runnerCharacter::MoveRight);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Pressed, this, &Aue_runnerCharacter::PrimaryFire);
	PlayerInputComponent->BindAction("PrimaryFire", IE_Released, this, &Aue_runnerCharacter::PrimaryFireRelease);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &Aue_runnerCharacter::Interact);
}

void Aue_runnerCharacter::MoveForward(float Value) {
	if (Value != 0.0f) {
		// get up vector
		const FVector Direction = FVector(1, 0, 0);
		AddMovementInput(Direction, Value);
	}
}

void Aue_runnerCharacter::MoveRight(float Value) {
	if (Value != 0.0f) {
		// get right vector 
		const FVector Direction = FVector(0, 1, 0);
		AddMovementInput(Direction, Value);
	}
}

void Aue_runnerCharacter::PrimaryFire() {
	primaryFireHeld = true;
	if (attackOnCooldown) return;

	UWorld* w = GetWorld();
	APlayerController* pc = UGameplayStatics::GetPlayerController(w, 0);

	FHitResult hit;

	pc->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, hit);

	FVector attackDirection = hit.ImpactPoint - GetActorTransform().GetLocation();
	attackDirection.Z = 0;
	attackDirection.Normalize();

	FVector spawnLocation = GetActorLocation() + attackDirection * 75;
	spawnLocation.Z -= 50.f;

	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetLocation(spawnLocation);
	SpawnTransform.SetRotation(attackDirection.Rotation().Quaternion());

	FActorSpawnParameters SpawnParams;

	ABulletActor* bulletActor = w->SpawnActor<ABulletActor>(BulletBP, SpawnTransform, SpawnParams);
	bulletActor->playerController = pc;

	attackOnCooldown = true;
	FTimerHandle attackTimer;
	GetWorldTimerManager().SetTimer(attackTimer, this, &Aue_runnerCharacter::PrimaryFireEpilogue, attackCooldown);
}

void Aue_runnerCharacter::PrimaryFireRelease() {
	primaryFireHeld = false;
}

void Aue_runnerCharacter::PrimaryFireEpilogue() {
	attackOnCooldown = false;
}

void Aue_runnerCharacter::Interact() {
	if (currentInteractable != NULL) {
		currentInteractable->Interact();
	}
}

void Aue_runnerCharacter::SetInteractable(class AInteractableActor* interactable) {
	currentInteractable = interactable;
}

void Aue_runnerCharacter::RemoveInteractable(class AInteractableActor* interactable) {
	if (currentInteractable != interactable) return;
	currentInteractable = NULL;
}

void Aue_runnerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (primaryFireHeld && !attackOnCooldown) {
		PrimaryFire();
	}
}
