// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "WorldDistraction.h"
#include "PlayerCharacter.h"
#include "DistractionManager.generated.h"

/**
 * 
 */
UCLASS()
class BREAKINGTHECYCLE_API ADistractionManager : public AInfo
{
	GENERATED_BODY()

public:

	ADistractionManager();

protected:

	virtual void BeginPlay();

	// Reference to Player Character
	APlayerCharacter* PlayerRef;

	// Reference to All World Distractions in Level
	TArray<AActor*> Distractions;

	UFUNCTION()
		void DistractionChangedEventFunction();

	
};
