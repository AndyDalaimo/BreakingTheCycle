// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HouseStateMachine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "NPC_AIController.h"
#include "HouseCharacter.generated.h"

UENUM(BlueprintType)
enum class EAnimIdleState : uint8
{
	IDLE = 0 UMETA(DisplayName = "Idle"),
	CONVERSATION = 1 UMETA(DisplayName = "Conversation"),
	NERVOUS = 2 UMETA(DisplayName = "Nervous")
};

UCLASS()
class BREAKINGTHECYCLE_API AHouseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHouseCharacter();

	// Get this Pawn's Behavior Tree
	class UBehaviorTree* GetBehaviorTree() const;

	// To be set when NPC interacts with Distraction item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		FVector DistractionLocation;

	UFUNCTION()
		FVector GetNextTargetLocation();
	
	UFUNCTION(BlueprintCallable)
		ENPCState GetThisCharacterState() const;

	UFUNCTION(BlueprintNativeEvent)
		void InitiateNPCConversationEvent();
	void InitiateNPCConversationEvent_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
		void EndNPCConversationEvent();
	void EndNPCConversationEvent_Implementation() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name", meta = (AllowPrivateAcces = "true"))
		ECharacterName CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		TArray<FVector> TargetLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		EAnimIdleState AnimIdleState;

	// Reference to its own AI Controller
	UPROPERTY()
	ANPC_AIController* AIControllerRef;

	// Current Target Location
	UPROPERTY()
	int currentLocIndex = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HouseState", meta = (AllowPrivateAccess = "true"))
		class AHouseStateMachine* HouseState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* Tree;



private:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
