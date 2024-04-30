// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GrimlessGameInstance.h"
#include "NoteData.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BREAKINGTHECYCLE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAcces = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAcces = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InventoryAction;


public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Allow Player to Interact with Note / World Item
	bool bCanInteract;
	bool bCanDistract;

	// Player Note Inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		TArray<FNoteStructure> NoteInventory;

	UFUNCTION()
		void AddNoteIntoInventory(FNoteStructure newNote, AActor* noteActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input Action Bound Functions
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void ShowInventory(const FInputActionValue& Value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:

	// Instance to Game Instance
	UGrimlessGameInstance* GameInstanceRef;

	// Limit control to other UIs if player is searching through their inventory
	bool bInventoryActive;

	// Note Interaction
	FNoteStructure NewNote;
	AActor* NoteToDestroy;

	// Distraction interation


};
