// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowCamera.h"

AFollowCamera::AFollowCamera(FObjectInitializer const& ObjectInitializer)
{


}

// -------------------------------------------------------------
// ---------------- Camera Adjustment Functions ----------------
// ------------- Change Position & Adjust Rotation -------------
// -------------------------------------------------------------

// New camera origin is passed in by RoomActors based on triggers detecting player movement
void AFollowCamera::ChangeCameraPosition(FVector origin)
{
	targetLocation = origin;
	currentPos = GetActorLocation();
	GetWorld()->GetTimerManager().ClearTimer(MovementTimer);
	// this->SetActorLocationAndRotation(origin, FRotator(0, 0, 0), false);

	MovementDelegate.BindUFunction(this, "LocTimerFunction");
	GetWorld()->GetTimerManager().SetTimer(MovementTimer, MovementDelegate, 0.01, true);

}


// New Camera Rotation 
// If true, Player is on left side of the room, rotate left
// If false, Player is on  right side of the room, rotate right
void AFollowCamera::ChangeCameraRotation(bool rotation, float rotationTarget, FVector origin)
{
	targetLocation = origin;
	switch (rotation)
	{
		case true:
			targetRot = -1.f* rotationTarget;
			currentYaw = GetActorRotation().Yaw;
			InterpToRotation();
			break;

		case false: 
			targetRot = rotationTarget;
			currentYaw = GetActorRotation().Yaw;
			InterpToRotation();
			break;
	}
}

void AFollowCamera::InterpToRotation()
{
	GetWorld()->GetTimerManager().ClearTimer(MovementTimer);
	TimerDelegate.BindUFunction(this, "RotTimerFunction");
	GetWorld()->GetTimerManager().SetTimer(MovementTimer, TimerDelegate, 0.01, true);
}

void AFollowCamera::RotTimerFunction()
{
	// UE_LOG(LogTemp, Warning, TEXT("Rot Timer Function Called"));
	if (currentYaw <= FMath::Abs(targetRot - 1))
	{
		this->SetActorRotation(FQuat::Slerp(GetActorRotation().Quaternion(), FRotator(cameraPitch, targetRot, 0).Quaternion(), .05));
		// this->SetActorLocationAndRotation(FMath::InterpSinIn(currentPos, targetLocation, 0.17), FQuat::Slerp(GetActorRotation().Quaternion(), FRotator(cameraPitch, targetRot, 0).Quaternion(), .05));
		currentYaw = GetActorRotation().Yaw;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("StopTimer"));
		GetWorld()->GetTimerManager().ClearTimer(MovementTimer);
	}
}

void AFollowCamera::LocTimerFunction()
{
	if (FVector::Distance(currentPos, targetLocation) > 1.0 || !GetActorRotation().IsNearlyZero(0.3))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Distance between locs: %f"), FVector::Distance(currentPos, targetLocation));
		this->SetActorLocationAndRotation(FMath::InterpSinIn(currentPos, targetLocation, 0.17), FQuat::Slerp(GetActorRotation().Quaternion(), FRotator(cameraPitch, 0, 0).Quaternion(), .05));
		currentPos = GetActorLocation();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("StopTimer"));
		GetWorld()->GetTimerManager().ClearTimer(MovementTimer);
	}
}
