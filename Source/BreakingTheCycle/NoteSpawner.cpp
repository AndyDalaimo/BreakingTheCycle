// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteSpawner.h"

// Sets default values
ANoteSpawner::ANoteSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	NoteSpawnerComp = CreateDefaultSubobject<USceneComponent>(TEXT("NoteSpawnerComp"));
	RootComponent = NoteSpawnerComp;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ANoteSpawner::OnBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ANoteSpawner::OnEndOverlap);

}



// Called when the game starts or when spawned
void ANoteSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}


// ----------------------------------------------------------------------
// ----------------------- Overlap and Drop Events ----------------------
// --- Drop the Correct note if the two characters meet in this spot ----
// ----------------------------------------------------------------------


void ANoteSpawner::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (Cast<AHouseCharacter>(OtherActor) && OtherComp)
	{
		if (CharactersToLookFor.Contains(Cast<AHouseCharacter>(OtherActor)->CharacterName))
		{
			DropNoteEvent(OtherActor);
		}
	}
}


void ANoteSpawner::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (Cast<AHouseCharacter>(OtherActor) && OtherComp)
	{
		CharactersToLookFor.Emplace(Cast<AHouseCharacter>(OtherActor)->CharacterName, false);
	}
}

void ANoteSpawner::DropNoteEvent(AActor* actor)
{
	bool bDropNote;

	CharactersToLookFor.Emplace(Cast<AHouseCharacter>(actor)->CharacterName, true);

	for (auto& Elem : CharactersToLookFor)
	{
		bDropNote = Elem.Value;
		if (bDropNote == false)
		{
			break;
		}
	}
	
	if (bDropNote)
	{
		UE_LOG(LogTemp, Warning, TEXT("Drop the note!"));
		AActor* BlueprintToSpawn;
		FActorSpawnParameters SpawnInfo;
		if (NoteBlueprintClass != nullptr)
		{
			BlueprintToSpawn = GetWorld()->SpawnActor<AActor>(NoteBlueprintClass, GetActorLocation(), FRotator::ZeroRotator, SpawnInfo);
			this->Destroy();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Dont drop it"));
	}

}

