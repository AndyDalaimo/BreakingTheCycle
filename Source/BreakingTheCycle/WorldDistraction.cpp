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
	
}

void AWorldDistraction::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherComp && PlayerRef != OtherActor)
	{
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
		}
	}
	else if (OtherActor == PlayerRef)
	{
		// TODO -- Player changes the distracted state when they want to i.e. on input
		DistractedState = EDistractedState::DISTRACTED;
		PlayerRef->bCanDistract = true;
	}
}

void AWorldDistraction::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (OtherActor == PlayerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has left distraction zone"));
		PlayerRef->bCanDistract = false;
	}
}

// Called every frame
void AWorldDistraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

