// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "GrimlessGameInstance.generated.h"

DECLARE_DELEGATE(FOnEndTimerDelegate);

/**
 * 
 */
UCLASS()
class BREAKINGTHECYCLE_API UGrimlessGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UGrimlessGameInstance(const FObjectInitializer& ObjectInitializer);
	
	// InventoryUI Reference to update when player adds Note to Inventory
	UPROPERTY()
	UUserWidget* InventoryUI;

	// Note Reference to update when player picks up a new Note
	UPROPERTY()
	UUserWidget* NoteUI;
	
	// Note Reference to update when player picks up a new Note
	UPROPERTY()
	UUserWidget* InteractUI;

	bool NoteUIActive;

	// Create Note UI and Show correct note on screen#
	UFUNCTION(BlueprintCallable)
		void ShowNoteUIWidget();

	// Event to cue SFX
	UFUNCTION(BlueprintNativeEvent)
		void NoteSFXEvent();
	void NoteSFXEvent_Implementation() { };

	// Event to Trigger End state of surviving the night
	UFUNCTION(BlueprintNativeEvent)
		void EndOfNightEvent();
	void EndOfNightEvent_Implementation() { };
	
	// Destroy Note UI and reset NoteUIActive
	UFUNCTION(BlueprintCallable)
		void HideNoteUIWidget();
	
	// Show Interact UI
	UFUNCTION(BlueprintCallable)
		void ShowInteractUIWidget();
	
	// Hide Interact UI
	UFUNCTION(BlueprintCallable)
		void HideInteractUIWidget();
	
	// Create Note UI and Show correct note on screen#
	UFUNCTION(BlueprintCallable)
		void ShowInventoryUIWidget();
	
	// Destroy Note UI and reset NoteUIActive
	UFUNCTION(BlueprintCallable)
		void HideInventoryUIWidget();

	

	// Initialize on Begin Play
	UFUNCTION(BlueprintCallable)
	virtual void init();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float TotalTime;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float TimerRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InGameMinutes;

	// Event broadcasted to actors indicating the in game timer has ended
	FOnEndTimerDelegate OnEndTimerEvent;

private:

	// Class Reference to Note UI and Inventory UI

	TSubclassOf<UUserWidget> NoteUIWidgetClass;
	TSubclassOf<UUserWidget> InventoryUIWidgetClass;
	TSubclassOf<UUserWidget> InteractUIWidgetClass;

	bool InventoryUIActive;

	// In Game timer
	FTimerHandle GameTimer;
	FTimerDelegate TimerDelegate;

	// In Game timer function to be called
	UFUNCTION()
		void GameTimerFunction();

};
