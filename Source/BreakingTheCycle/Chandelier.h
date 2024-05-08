// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HouseCharacter.h"
#include "Components/BoxComponent.h"
#include "Chandelier.generated.h"

UCLASS()
class BREAKINGTHECYCLE_API AChandelier : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ChandelierMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollider;
	
public:	
	// Sets default values for this actor's properties
	AChandelier();

	UFUNCTION(BlueprintNativeEvent)
		void CharacterInteractionEvent();
	void CharacterInteractionEvent_Implementation() { };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap Event When Player is in range of Distraction Object
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

private:
	class AHouseCharacter* NPCRef;

};
