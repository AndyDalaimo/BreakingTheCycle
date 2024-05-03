// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseStateMachine.h"

AHouseStateMachine::AHouseStateMachine()
{

}



void AHouseStateMachine::BeginPlay()
{
	Super::BeginPlay();
}




// -----------------------------------------------------------------------------
// ------------------- State Machine Helper Fucntions --------------------------
// -----------------------------------------------------------------------------


// Change the state of one of the Characters in the world
void AHouseStateMachine::ChangeCharacterState(FCurrentState newState)
{
	for (int i = 0; i < CharacterStates.Num(); i++)
	{
		if (newState.Character == CharacterStates[i].Character)
		{
			CharacterStates[i].State = newState.State;
			// UE_LOG(LogTemp, Warning, TEXT("%s state has changed"), UEnum::GetNameStringByValue(CharacterStates[i].Character);
			continue;
		}
	}
}

ENPCState AHouseStateMachine::GetThisNPCState(ECharacterName name)
{
	for (int i = 0; i < CharacterStates.Num(); i++)
	{
		if (name == CharacterStates[i].Character)
		{
			return CharacterStates[i].State;
			continue;
		}
	}

	return ENPCState::DEAD;
}
