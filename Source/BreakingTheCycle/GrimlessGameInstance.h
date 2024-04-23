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
	
	// Inventory Reference to update when player adds Note to Inventory
	UUserWidget* InventoryUI;

	// Create Note UI and Show correct note on screen#
	UFUNCTION(BlueprintCallable)
		void ShowNoteUIWidget();
	
	// Destroy Note UI and reset NoteUIActive
	UFUNCTION(BlueprintCallable)
		void DestroyNoteUIWidget();
	
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

	bool NoteUIActive;
	bool InventoryUIActive;

};
