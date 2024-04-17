// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "NoteData.h"
#include "HouseStateMachine.generated.h"

/**
 * 
 */
UCLASS()
class BREAKINGTHECYCLE_API AHouseStateMachine : public AInfo
{
	GENERATED_BODY()

public:
	
	AHouseStateMachine();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NoteData")
		UNoteData* NoteDataSet;

protected:

	virtual void BeginPlay();
	
};
