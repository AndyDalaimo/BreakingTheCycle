// Fill out your copyright notice in the Description page of Project Settings.


#include "Chandelier.h"

// Sets default values
AChandelier::AChandelier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ChandelierMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChandelierMesh"));
	RootComponent = ChandelierMesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AChandelier::OnBeginOverlap);


}



// Called when the game starts or when spawned
void AChandelier::BeginPlay()
{
	Super::BeginPlay();
	
	GameInstanceRef = Cast<UGrimlessGameInstance>(GetWorld()->GetGameInstance());

	if (GameInstanceRef != nullptr) GameInstanceRef->OnEndTimerEvent.BindUObject(this, &AChandelier::InGameTimerEndedEvent);

}



// -----------------------------------------------------------------------
// ------------------- House Character Interaction -----------------------
// -----------------------------------------------------------------------


void AChandelier::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	NPCRef = CastChecked<AHouseCharacter>(OtherActor);

	if (NPCRef != nullptr)
	{
		if (NPCRef->CharacterName == ECharacterName::SINGER)
		{
			UE_LOG(LogTemp, Warning, TEXT("This is the Singer"));
			CharacterInteractionEvent(NPCRef->CharacterName);
		}
		else if (NPCRef->CharacterName == ECharacterName::NOBLEMAN)
		{
			UE_LOG(LogTemp, Warning, TEXT("This is the Nobleman who will die"));
			CharacterInteractionEvent(NPCRef->CharacterName);

		}
	}
}


// Bound Delegate event that will trigger when the In Game timer has ended
void AChandelier::InGameTimerEndedEvent()
{
	bEndSequenceTriggered = true;
}