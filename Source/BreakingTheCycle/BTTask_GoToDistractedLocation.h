// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GoToDistractedLocation.generated.h"

/**
 * 
 */
UCLASS()
class BREAKINGTHECYCLE_API UBTTask_GoToDistractedLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_GoToDistractedLocation(FObjectInitializer const& ObjectInitializer);
	virtual  EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
