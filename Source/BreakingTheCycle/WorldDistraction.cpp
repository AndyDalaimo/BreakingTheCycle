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
	if (CastChecked<AHouseCharacter>(OtherActor) && OtherComp)
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

			NPC->TargetLocations[NPC->currentLocIndex] = this->DistractionLocation->GetComponentLocation();
			NPC->DistractionLocation = this->DistractionLocation->GetComponentLocation();
		}
	}
}

// Called every frame
void AWorldDistraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

