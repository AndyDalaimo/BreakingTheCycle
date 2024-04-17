// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "GrimlessGameInstance.h"
#include "Components/BoxComponent.h"
#include "WorldNotes.generated.h"

UCLASS()
class BREAKINGTHECYCLE_API AWorldNotes : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* NoteMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAcces = "true"))
		UBoxComponent* BoxCollider;
	

	
public:	
	// Sets default values for this actor's properties
	AWorldNotes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap Event When Player is in range to pickup Note 
	UFUNCTION()
		void OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	
	// Overlap Event When Player is in range to pickup Note 
	UFUNCTION()
		void OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	// Reference to Player
	APlayerCharacter* PlayerRef;

	// Reference to Game Instance
	UGrimlessGameInstance* GameInstanceRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
