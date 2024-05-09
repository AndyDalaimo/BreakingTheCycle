// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HouseCharacter.h"
#include "PlayerCharacter.h"
#include "HouseStateMachine.h"
#include "GrimlessGameInstance.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "WorldDistraction.generated.h"

UENUM(BlueprintType)
enum class EDistractedState : uint8
{
	NEUTRAL = 0 UMETA(DisplayName = "Neutral"),
	DISTRACTED = 1 UMETA(DisplayName = "Distracted")
};

UCLASS()
class BREAKINGTHECYCLE_API AWorldDistraction : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* DistractionMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* DistractionLocation;

	
public:	
	// Sets default values for this actor's properties
	AWorldDistraction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		EDistractedState DistractedState;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
		ECharacterName NPCToDistract;

	UPROPERTY(EditAnywhere, Category = "AI|PlayerInteraction", meta = (AllowPrivateAccess = "true"))
		FString DistractionName;

	UFUNCTION(BlueprintNativeEvent)
		void PlayerTriggeredEventState();
	void PlayerTriggeredEventState_Implementation() {};	
	
	UFUNCTION(BlueprintNativeEvent)
		void ResolvedEventState();
	void ResolvedEventState_Implementation() {};

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

	// Overlap Event When Player is in range of Distraction Object
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	// TESTING
	bool bInteracting;

	// Reference to Player
	APlayerCharacter* PlayerRef;

	// Reference to AI_NPC
	class AHouseCharacter* NPC;

	// Reference to HouseStateMachine
	AHouseStateMachine* HouseStateRef;

	// Reference to Game Instance
	UGrimlessGameInstance* GameInstanceRef;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
