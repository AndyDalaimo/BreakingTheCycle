// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HouseStateMachine.h"
#include "NoteData.generated.h"


UENUM(BlueprintType)
enum class ENoteType : uint8
{
	None = 0 UMETA(Hidden),
	HINT = 1 UMETA(DisplayName = "Hint"),
	LORE = 2 UMETA(DisplayName = "Lore")
};

USTRUCT(BlueprintType)
struct FNoteStructure
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NoteStructure")
		ECharacterName Character;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NoteStructure")
		ENoteType NoteType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NoteStructure")
		FString Note; 
};

/**
 * 
 */
UCLASS()
class BREAKINGTHECYCLE_API UNoteData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notes")
		TArray<FNoteStructure> WorldNotes;
	
};
