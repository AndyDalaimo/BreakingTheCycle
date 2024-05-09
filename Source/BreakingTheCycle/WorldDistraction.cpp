// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldDistraction.h"

// Sets default values
AWorldDistraction::AWorldDistraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DistractionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DistractionMesh"));
	RootComponent = DistractionMesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AWorldDistraction::OnBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AWorldDistraction::OnEndOverlap);

	DistractionLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("DistractionLocation"));
	DistractionLocation->SetupAttachment(RootComponent);
	DistractionLocation->SetRelativeRotation(FRotator(90, 0, 0));
}

// Called when the game starts or when spawned
void AWorldDistraction::BeginPlay()
{
	Super::BeginPlay();

	HouseStateRef = Cast<AHouseStateMachine>(UGameplayStatics::GetActorOfClass(GetWorld(), AHouseStateMachine::StaticClass()));

	PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	GameInstanceRef = Cast<UGrimlessGameInstance>(GetWorld()->GetGameInstance());
	
}

void AWorldDistraction::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherComp && PlayerRef != OtherActor && !bInteracting)
	{
		bInteracting = true;
		NPC = Cast<AHouseCharacter>(OtherActor);
		if (DistractedState == EDistractedState::DISTRACTED && NPC->CharacterName == NPCToDistract)
		{
			// Set the state of this NPC in the HOUSESTATEMACHINE actor in world
			UE_LOG(LogTemp, Display, TEXT("Distract this NPC"));
			
			FCurrentState state;
			state.Character = NPCToDistract;
			state.State = ENPCState::SUSPICIOUS;
			HouseStateRef->ChangeCharacterState(state);

			// Update Distraction Location and reset state for Distraction Actor
			NPC->DistractionLocation = this->DistractionLocation->GetComponentLocation();
			DistractedState = EDistractedState::NEUTRAL;

			// !!!!!! Set a delay to resolve this state after the character reaches the distracted location !!!!!
			this->ResolvedEventState();
		}
	}
	else if (OtherActor == PlayerRef && !bInteracting)
	{
		bInteracting = true;
		// Call BlueprintEvent for this Actor's Distraction Event
		// PlayerTriggeredEventState();
		GameInstanceRef->ShowInteractUIWidget();
		PlayerRef->ChangeDistractionState(DistractionName);
		PlayerRef->bCanDistract = true;
	}
}

void AWorldDistraction::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (OtherActor == PlayerRef && bInteracting)
	{
		bInteracting = false;
		UE_LOG(LogTemp, Warning, TEXT("Player has left distraction zone"));
		GameInstanceRef->HideInteractUIWidget();
		PlayerRef->bCanDistract = false;
		PlayerRef->ChangeDistractionState("");
	}
	else if (Cast<AHouseCharacter>(OtherActor)) {
		bInteracting = false;
	}
}

// Called every frame
void AWorldDistraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

