// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : bCanInteract(false), bCanDistract(false), bInventoryActive(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	// GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}



// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameInstanceRef = Cast<UGrimlessGameInstance>(GetWorld()->GetGameInstance());

	// Add Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up Action Bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		
		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);

		// Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &APlayerCharacter::ShowInventory);
	}

}

// ---------------------------------------------------------------------
// ----------------------- Input Functions -----------------------------
// ---------------------------------------------------------------------


// Movement is in 3D to for player to float in all degrees of movement
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector MovementVector = Value.Get<FVector>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// get up vector
		const FVector UpDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		AddMovementInput(UpDirection, MovementVector.Z);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACT"));

	if (bCanInteract && NoteToDestroy) 
	{
		// Push new note into memory
		NoteInventory.Push(NewNote);
		NoteToDestroy->Destroy();

		// Reset temp Note
		NewNote = FNoteStructure();
		NoteToDestroy = nullptr;

		GameInstanceRef->ShowNoteUIWidget(); 
		return;
	}
	if (bCanDistract)
	{
		// Change state of this distraction Actor
		HandleDistractionEvent();
		
	}
	if (GameInstanceRef->NoteUIActive)
	{
		GameInstanceRef->HideNoteUIWidget();
	}
}

void APlayerCharacter::ShowInventory(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Show Inventory"));

	if (!bCanInteract && !bInventoryActive) 
	{ 
		GameInstanceRef->ShowInventoryUIWidget(); 
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		bInventoryActive = true;
	}
	else if (bInventoryActive)
	{
		GameInstanceRef->HideInventoryUIWidget();
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		bInventoryActive = false;
	}
}


// ---------------------------------------------------------------------
// ---------------------- World Interactions ---------------------------
// ---------------------------------------------------------------------

void APlayerCharacter::AddNoteIntoInventory(FNoteStructure newNote, AActor* noteActor)
{
	NewNote = newNote;
	NoteToDestroy = noteActor;
}

void APlayerCharacter::ChangeDistractionState(FString distractionName)
{
	DistractionToTrigger = distractionName;
}

void APlayerCharacter::HandleDistractionEvent()
{
	OnDistractionStateChanged.ExecuteIfBound();
}
