// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ARoomActor::ARoomActor() : bPlayerInRoom(false), SwingTarget(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseRoomCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BaseRoomCollider"));
	BaseRoomCollider->SetupAttachment(RootComponent);
	BaseRoomCollider->OnComponentBeginOverlap.AddDynamic(this, &ARoomActor::ChangeCameraOrigin);

	LeftRoomCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftRoomCollider"));
	LeftRoomCollider->SetupAttachment(BaseRoomCollider);
	LeftRoomCollider->OnComponentBeginOverlap.AddDynamic(this, &ARoomActor::AdjustCameraRotationLeft);
	
	RightRoomCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("RightRoomCollider"));
	RightRoomCollider->SetupAttachment(BaseRoomCollider);
	RightRoomCollider->OnComponentBeginOverlap.AddDynamic(this, &ARoomActor::AdjustCameraRotationRight);

}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	CameraRef = Cast<AFollowCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), AFollowCamera::StaticClass()));
}



// Called every frame
/*void ARoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/


// -------------------------------------------------------------
// ---------------- Camera Adjustment Function -----------------
// -------------- Change Origin & Adjust Rotation --------------
// -------------------------------------------------------------


void ARoomActor::ChangeCameraOrigin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == PlayerRef)
	{
		bPlayerInRoom = true;
		UE_LOG(LogTemp, Warning, TEXT("Player InRoom"));
		CameraRef->ChangeCameraPosition(OriginPoint);

	}
}

void ARoomActor::AdjustCameraRotationLeft(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// if (OtherActor == PlayerRef && bPlayerInRoom)
	if (OtherActor == PlayerRef)
	{
		if (CameraRef->GetActorRotation().Yaw <= 1.0) CameraRef->ChangeCameraRotation(true, SwingTarget, OriginPoint);
		// if (CameraRef->GetActorRotation().Yaw >= 10.0) CameraRef->ChangeCameraPosition(OriginPoint);
		
	}
}

void ARoomActor::AdjustCameraRotationRight(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// if (OtherActor == PlayerRef && bPlayerInRoom)
	if (OtherActor == PlayerRef)
	{
		if (CameraRef->GetActorRotation().Yaw >= -1.0) CameraRef->ChangeCameraRotation(false, SwingTarget, OriginPoint);
		// if (CameraRef->GetActorRotation().Yaw <= -10.0) CameraRef->ChangeCameraPosition(OriginPoint);

	}
}
