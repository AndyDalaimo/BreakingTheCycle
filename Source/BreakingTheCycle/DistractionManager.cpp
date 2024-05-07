// Fill out your copyright notice in the Description page of Project Settings.


#include "DistractionManager.h"

#include "Kismet/GameplayStatics.h"

ADistractionManager::ADistractionManager()
{

}



void ADistractionManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldDistraction::StaticClass(), Distractions);

	for (AActor* dist : Distractions)
	{
		UE_LOG(LogTemp, Warning, TEXT("Distraction Actor: %s"), *Cast<AWorldDistraction>(dist)->DistractionName);
	}
	
	if (PlayerRef)
	{
		PlayerRef->OnDistractionStateChanged.BindUObject(this, &ADistractionManager::DistractionChangedEventFunction);
	}
}

// Change the Distraction state when the Player interacts with this WorldDistraciton Actor
// Delegate Function bound in Player Character
void ADistractionManager::DistractionChangedEventFunction()
{
	for (AActor* dist : Distractions)
	{
		if (PlayerRef->DistractionToTrigger == Cast<AWorldDistraction>(dist)->DistractionName)
		{
			if (Cast<AWorldDistraction>(dist)->DistractedState == EDistractedState::DISTRACTED)
			{
				Cast<AWorldDistraction>(dist)->DistractedState = EDistractedState::NEUTRAL;
				Cast<AWorldDistraction>(dist)->ResolvedEventState();
			}
			else {
				Cast<AWorldDistraction>(dist)->DistractedState = EDistractedState::DISTRACTED;
				Cast<AWorldDistraction>(dist)->PlayerTriggeredEventState();
			}
		}
	}
}
