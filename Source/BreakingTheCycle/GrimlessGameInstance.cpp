// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimlessGameInstance.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


UGrimlessGameInstance::UGrimlessGameInstance(const FObjectInitializer& ObjectInitializer)
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> NoteUIFinder(TEXT("/Game/UI/WBP_Note"));
	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryUIFinder(TEXT("/Game/UI/WBP_Inventory"));

	if (!NoteUIFinder.Succeeded() && !InventoryUIFinder.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("UI NOT FOUND"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("UI FOUND"));
		NoteUIWidgetClass = NoteUIFinder.Class;
		InventoryUIWidgetClass = InventoryUIFinder.Class;
	}
}

// Initialize New Game Instance and set up Inventory Widget
void UGrimlessGameInstance::init()
{
	// Create Inventory reference to use later	
	InventoryUI = CreateWidget<UUserWidget>(this, InventoryUIWidgetClass);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, InventoryUI ? InventoryUI->GetName() : "Not Valid");
}


// ---------------------------------------------------------------------
// ------------------------ UI Functions -------------------------------
// ---------------------------------------------------------------------

void UGrimlessGameInstance::ShowNoteUIWidget()
{
	if (!NoteUIActive)
	{
		UUserWidget* NoteUI = CreateWidget<UUserWidget>(this, NoteUIWidgetClass);
		NoteUI->AddToViewport();
		NoteUIActive = true;
		UE_LOG(LogTemp, Display, TEXT("Showing Note UI Widget"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, NoteUI ? NoteUI->GetName() : "Not valid");
	}
}

void UGrimlessGameInstance::DestroyNoteUIWidget()
{
	if (NoteUIActive)
	{
		// Remove All widget -----> Change later
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		NoteUIActive = false;
		UE_LOG(LogTemp, Display, TEXT("Destroying Note UI Widget"));
	}
}

void UGrimlessGameInstance::ShowInventoryUIWidget()
{
	if (!InventoryUIActive && InventoryUI)
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
		InventoryUI->RemoveFromViewport();
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

