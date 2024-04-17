// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimlessGameInstance.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


UGrimlessGameInstance::UGrimlessGameInstance(const FObjectInitializer& ObjectInitializer)
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> NoteUIFinder(TEXT("/Game/UI/WBP_Note"));

	if (!NoteUIFinder.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("UI NOT FOUND"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("UI FOUND"));
		NoteUIWidgetClass = NoteUIFinder.Class;
	}
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, NoteUI ? NoteUI->GetName() : "Not valid");
	}
}

void UGrimlessGameInstance::DestroyNoteUIWidget()
{
	if (NoteUIActive)
	{
		// Remove All widget ----- Change later
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	}
}
