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
}

// Called when the game starts or when spawned
void AWorldDistraction::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	DistractedState = EDistractedState::DISTRACTED;
	
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
		UE_LOG(LogTemp, Display, TEXT("NPC is in Distraction Area"));
		if (DistractedState == EDistractedState::DISTRACTED)
		{
			// Set the state of this NPC in the HOUSESTATEMACHINE actor in world -- Need Reference
			UE_LOG(LogTemp, Display, TEXT("Distract this NPC"));
		}
	}
}

// Called every frame
void AWorldDistraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

