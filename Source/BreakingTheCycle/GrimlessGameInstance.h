// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "GrimlessGameInstance.generated.h"

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
	UUserWidget* InventoryUI;

	// Note Reference to update when player picks up a new Note
	UUserWidget* NoteUI;
	bool NoteUIActive;

	// Create Note UI and Show correct note on screen#
	UFUNCTION(BlueprintCallable)
		void ShowNoteUIWidget();
	
	// Destroy Note UI and reset NoteUIActive
	UFUNCTION(BlueprintCallable)
		void HideNoteUIWidget();
	
	// Create Note UI and Show correct note on screen#
	UFUNCTION(BlueprintCallable)
		void ShowInventoryUIWidget();
	
	// Destroy Note UI and reset NoteUIActive
	UFUNCTION(BlueprintCallable)
		void HideInventoryUIWidget();

	// Initialize on Begin Play
	UFUNCTION(BlueprintCallable)
	virtual void init();

private:

	// Class Reference to Note UI and Inventory UI
	TSubclassOf<UUserWidget> NoteUIWidgetClass;
	TSubclassOf<UUserWidget> InventoryUIWidgetClass;

	bool InventoryUIActive;

};
