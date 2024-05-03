// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ResolveDistraction.h"

#include "HouseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HouseStateMachine.h"

UBTTask_ResolveDistraction::UBTTask_ResolveDistraction(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Resolve Distraction and Update NPC State";
}

EBTNodeResult::Type UBTTask_ResolveDistraction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller and its NPC 
	if (auto* const controller = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{

		if (AHouseCharacter* const npc = Cast<AHouseCharacter>(controller->GetPawn()))
		{

			// Reset the Distracted State to re-initiate patrol path
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("Distracted"), false);

			// Distraction is resolved, continue to patrol path once again
			AHouseStateMachine* HouseRef = Cast<AHouseStateMachine>(UGameplayStatics::GetActorOfClass(GetWorld(), AHouseStateMachine::StaticClass()));
			FCurrentState state;
			state.Character = npc->CharacterName;
			state.State = ENPCState::HUNTED;
			HouseRef->ChangeCharacterState(state);

			// Finish with Success
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;

		}
	}



	return EBTNodeResult::Failed;
}
