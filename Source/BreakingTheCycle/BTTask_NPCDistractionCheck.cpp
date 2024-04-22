// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NPCDistractionCheck.h"

#include "HouseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_NPCDistractionCheck::UBTTask_NPCDistractionCheck(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Is NPC Distracted?";
}

EBTNodeResult::Type UBTTask_NPCDistractionCheck::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller and its NPC 
	if (auto* const controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{

		if (AHouseCharacter* const npc = Cast<AHouseCharacter>(controller->GetPawn()))
		{
			// Stop patrolling and go Check distraction
			if (npc->GetThisCharacterState() == ENPCState::SUSPICIOUS)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
			}

			// Finish with Success
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;

		}
	}


	return EBTNodeResult::Failed;
}
