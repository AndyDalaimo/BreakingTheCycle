// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindNextTargetLocation.h"

#include "HouseCharacter.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindNextTargetLocation::UBTTask_FindNextTargetLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Next Target Location for NPC";
}

EBTNodeResult::Type UBTTask_FindNextTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller and its NPC 
	if (auto* const controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if (AHouseCharacter* const npc = Cast<AHouseCharacter>(controller->GetPawn()))
		{
			// If this character is DEAD, drop from tree finding next target location
			if (npc->GetThisCharacterState() == ENPCState::SUSPICIOUS || npc->GetThisCharacterState() == ENPCState::DEAD) return EBTNodeResult::Failed;

			FNavLocation Location;
			Location.Location = npc->GetNextTargetLocation();
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);

			// Finish with Success
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
