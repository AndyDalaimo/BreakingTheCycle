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
	

	// Create Note UI and Show correct note on screen#
	UFUNCTION(BlueprintCallable)
		void ShowNoteUIWidget();
	
	// Destroy Note UI and reset NoteUIActive
	UFUNCTION(BlueprintCallable)
		void DestroyNoteUIWidget();


private:

	// Class Reference to Note UI 
	TSubclassOf<UUserWidget> NoteUIWidgetClass;
	bool NoteUIActive;
};
