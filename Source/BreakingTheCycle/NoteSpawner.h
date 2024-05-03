// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HouseCharacter.h"
#include "WorldNotes.h"
#include "Components/BoxComponent.h"
#include "NoteSpawner.generated.h"

UCLASS()
class BREAKINGTHECYCLE_API ANoteSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SceneComp, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* NoteSpawnerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollider;

	
public:	
	// Sets default values for this actor's properties
	ANoteSpawner();

	// NPCs required to drop note
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note|Interaction", meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterName, bool> CharactersToLookFor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Note", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> NoteBlueprintClass;

protected:
	// Event to drop the note 
	UFUNCTION()
		void DropNoteEvent(AActor* actor);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap Event When Player is in range of Note Spawner
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);


	// Overlap Event When Player is in range of Note Spawner
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);


};
