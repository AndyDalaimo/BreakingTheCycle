// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"

#include "HouseCharacter.h"

ANPC_AIController::ANPC_AIController(FObjectInitializer const& ObjectInitializer)
{
}



// On Possession of the pawn, use the specified behavior tree if there is not one
void ANPC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AHouseCharacter* const npc = Cast<AHouseCharacter>(InPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree())
		{
			UBlackboardComponent* bb;
			UseBlackboard(tree->BlackboardAsset, bb);
			Blackboard = bb;
			RunBehaviorTree(tree);
		}
	}
}