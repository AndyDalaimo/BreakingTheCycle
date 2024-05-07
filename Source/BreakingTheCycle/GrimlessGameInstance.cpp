// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimlessGameInstance.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


UGrimlessGameInstance::UGrimlessGameInstance(const FObjectInitializer& ObjectInitializer) : TotalTime(0.f), InGameMinutes(3.f), TimerRate(1.f)
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> NoteUIFinder(TEXT("/Game/UI/WBP_Note"));
	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryUIFinder(TEXT("/Game/UI/WBP_Inventory"));
	static ConstructorHelpers::FClassFinder<UUserWidget> InteractUIFinder(TEXT("/Game/UI/WBP_Interact"));

	if (!NoteUIFinder.Succeeded() && !InventoryUIFinder.Succeeded() && !InteractUIFinder.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("UI NOT FOUND"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("UI FOUND"));
		NoteUIWidgetClass = NoteUIFinder.Class;
		InventoryUIWidgetClass = InventoryUIFinder.Class;
		InteractUIWidgetClass = InteractUIFinder.Class;
	}
}

// Initialize New Game Instance and set up Inventory Widget
void UGrimlessGameInstance::init()
{
	// Create InventoryUI and NoteUI reference to use later	
	InventoryUI = CreateWidget<UUserWidget>(this, InventoryUIWidgetClass);
	NoteUI = CreateWidget<UUserWidget>(this, NoteUIWidgetClass);
	InteractUI = CreateWidget<UUserWidget>(this, InteractUIWidgetClass);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, InventoryUI ? InventoryUI->GetName() : "Not Valid");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, NoteUI ? NoteUI->GetName() : "Not Valid");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, InteractUI ? InteractUI->GetName() : "Not Valid");

	// Trigger In Game timer to start countdown to Midnight (End game sequence)
	TotalTime = (60.f * InGameMinutes);

	TimerDelegate.BindUFunction(this, "GameTimerFunction");
	GetWorld()->GetTimerManager().SetTimer(GameTimer, TimerDelegate, TimerRate, true);
}


// In game timer function. 
// Will countdown to an end game sequence to switch AI behavior 
// and trigger win/loss conditions for Player
void UGrimlessGameInstance::GameTimerFunction()
{
	TotalTime--;
	UE_LOG(LogTemp, Warning, TEXT("Time Left: %f"), TotalTime);

	if (TotalTime <= 0)
	{
		GetTimerManager().ClearTimer(GameTimer);
	}
	if (!GameTimer.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Timer Cleared"));
	}
}


// ---------------------------------------------------------------------
// ------------------------ UI Functions -------------------------------
// ---------------------------------------------------------------------

void UGrimlessGameInstance::ShowNoteUIWidget()
{
	if (!NoteUIActive && NoteUI != nullptr)
	{
		NoteUI->AddToViewport();
		NoteUIActive = true;
		// UE_LOG(LogTemp, Display, TEXT("Showing Note UI Widget"));
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, NoteUI ? NoteUI->GetName() : "Not valid");
	}
}

void UGrimlessGameInstance::HideNoteUIWidget()
{
	if (NoteUIActive)
	{
		// Remove All widget -----> Change later
		NoteUI->RemoveFromParent();
		NoteUIActive = false;
		// UE_LOG(LogTemp, Display, TEXT("Hiding Note UI Widget"));
	}
}

void UGrimlessGameInstance::ShowInteractUIWidget()
{
	if (InteractUI != nullptr) InteractUI->AddToViewport();
}



void UGrimlessGameInstance::HideInteractUIWidget()
{
	InteractUI->RemoveFromParent();
}

void UGrimlessGameInstance::ShowInventoryUIWidget()
{
	if (!InventoryUIActive && InventoryUI != nullptr)
	{
		// UUserWidget* InventoryUI = CreateWidget<UUserWidget>(this, InventoryUIWidgetClass);
		InventoryUI->AddToViewport();
		InventoryUIActive = true;

		UE_LOG(LogTemp, Display, TEXT("Showing Inventory UI Widget"));

		// Reference to Player Controller
		APlayerController* PlayerController = GetFirstLocalPlayerController();

		// Set Up Input Parameters
		// FInputModeUIOnly InputModeData;
		FInputModeGameAndUI InputModeData;

		InputModeData.SetWidgetToFocus(InventoryUI->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		// Set Input Modes
		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = true;

	}
}

void UGrimlessGameInstance::HideInventoryUIWidget()
{
	if (InventoryUIActive)
	{
		// Remove All widget -----> Change later
		// UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		InventoryUI->RemoveFromParent();
		InventoryUIActive = false;

		UE_LOG(LogTemp, Display, TEXT("Hiding Inventory UI Widget"));

		APlayerController* PlayerController = GetFirstLocalPlayerController();

		// Set up input parameters for player controller in Game
		FInputModeGameOnly InputModeData;
		InputModeData.SetConsumeCaptureMouseDown(true);


		// Set Input Mode
		PlayerController->SetInputMode(InputModeData);
		// PlayerController->SetInputMode(MouseInputData);
		PlayerController->bShowMouseCursor = false;
	}
}

