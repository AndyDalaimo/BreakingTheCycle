// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "NoteData.h"
#include "HouseStateMachine.generated.h"

UENUM(BlueprintType)
enum class ENPCState : uint8
{
	CALM = 0 UMETA(DisplayName = "Calm"),
	HUNTED = 1 UMETA(DisplayName = "Hunted"),
	SUSPICIOUS = 2 UMETA(DisplayName = "Suspicious")
};

USTRUCT(BlueprintType)
struct FCurrentState
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|CurrentCharacterState")
		FName Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State|CurrentCharacterState")
		ENPCState State;
};

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

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "State")
		TArray<FCurrentState> CharacterStates;

	UFUNCTION(BlueprintCallable)
		void ChangeCharacterState(FCurrentState newState);

protected:

	virtual void BeginPlay();
	
};
