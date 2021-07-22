// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ue_runnerCharacter.generated.h"

UCLASS(config=Game)
class Aue_runnerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AActor> bulletBP;

	UPROPERTY(EditAnywhere, Category = "Attack")
	class UWeaponElementData* currentElement;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TArray<class UWeaponElementData*> elementTypes;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float attackCooldown = 0.5f;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool attackOnCooldown = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool primaryFireHeld = false;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TArray<TSubclassOf<class AActor>> bulletTypes;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TScriptInterface<IInteractableObject> currentInteractable;

public:
	Aue_runnerCharacter();

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void PrimaryFire();
	void PrimaryFireRelease();
	void PrimaryFireEpilogue();

	void Interact();

protected:

	virtual void BeginPlay() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	void SetInteractable(TScriptInterface<class IInteractableObject> interactable);

	UFUNCTION()
	void RemoveInteractable(TScriptInterface<class IInteractableObject> interactable);

	UFUNCTION(BlueprintCallable)
	void SetBullet(int bulletIndex, float newAttackCooldown);

	UFUNCTION(BlueprintCallable)
	void SetWeaponElement(int elementIndex);

	UPROPERTY(BlueprintReadWrite)
	class UUserWidget* GameUI;
};