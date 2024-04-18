// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseCharacter.h"

// Sets default values
AHouseCharacter::AHouseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void AHouseCharacter::BeginPlay()
{
	Super::BeginPlay();

	HouseState = Cast<AHouseStateMachine>(UGameplayStatics::GetActorOfClass(GetWorld(), AHouseStateMachine::StaticClass()));
	
}

// Called every frame
void AHouseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHouseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

// Return this Pawn's Behavior Tree
UBehaviorTree* AHouseCharacter::GetBehaviorTree() const
{
	return Tree;
}

FVector AHouseCharacter::GetNextTargetLocation()
{
	FVector resultLoc;
	if (!TargetLocations.IsEmpty())
	{
		if (currentLocIndex >= TargetLocations.Num())
		{
			currentLocIndex = 0;
			resultLoc = TargetLocations[currentLocIndex];
		}
		else {
			resultLoc = TargetLocations[currentLocIndex];
			currentLocIndex++;
		}
	}
	return resultLoc;
}
