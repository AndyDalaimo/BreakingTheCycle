// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoToDistractedLocation.h"

#include "HouseCharacter.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GoToDistractedLocation::UBTTask_GoToDistractedLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Go to Distraction Location and Wait";
}

EBTNodeResult::Type UBTTask_GoToDistractedLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller and its NPC
	if (auto* const controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		if (AHouseCharacter* const npc = Cast<AHouseCharacter>(controller->GetPawn()))
		{
			if (npc->GetThisCharacterState() == ENPCState::SUSPICIOUS)
			{
				FNavLocation Location;
				Location.Location = npc->DistractionLocation;

				// Set new location for the NPC to go investigate
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location.Location);
	
				// Finish with Success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
