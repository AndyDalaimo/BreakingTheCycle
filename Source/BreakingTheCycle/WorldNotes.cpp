// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldNotes.h"

// Sets default values
AWorldNotes::AWorldNotes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	NoteMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NoteMesh"));
	RootComponent = NoteMesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AWorldNotes::OnPlayerBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AWorldNotes::OnPlayerEndOverlap);
}

// Called when the game starts or when spawned
void AWorldNotes::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	GameInstanceRef = Cast<UGrimlessGameInstance>(GetWorld()->GetGameInstance());
}

// Overlap Function to allow player to interact with note
void AWorldNotes::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor == PlayerRef && OtherComp)
	{
		UE_LOG(LogTemp, Display, TEXT("Player CAN Interact with Note"));
		AddNoteIntoPlayerInventory();
		PlayerRef->bCanInteract = true;

	}
}

// Exit from the Note UI if Player leaves the area
void AWorldNotes::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	if (OtherActor == PlayerRef)
	{
		UE_LOG(LogTemp, Display, TEXT("Player CANNOT Interact with Note"));
		PlayerRef->bCanInteract = false;
		GameInstanceRef->HideNoteUIWidget();
	}
}

void AWorldNotes::AddNoteIntoPlayerInventory()
{
	PlayerRef->AddNoteIntoInventory(Note, (AActor*)this);
}

// Called every frame
void AWorldNotes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

