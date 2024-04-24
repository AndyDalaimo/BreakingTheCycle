// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "FollowCamera.generated.h"

/**
 * 
 */
UCLASS()
class BREAKINGTHECYCLE_API AFollowCamera : public ACameraActor
{
	GENERATED_BODY()

public:

	AFollowCamera(FObjectInitializer const& ObjectInitializer);

	UFUNCTION()
		void ChangeCameraPosition(FVector origin);

	UFUNCTION()
		void ChangeCameraRotation(bool rotation);

protected:


	double targetRot;

	// Call timeline smoothly transition camera to target Rotation
	UFUNCTION()
	void InterpToRotation(double targetYaw);


	// Properties for in game timer
	FTimerHandle MovementTimer;
	FTimerDelegate TimerDelegate;
	FTimerDelegate MovementDelegate;
	double currentYaw;
	FVector currentPos;
	FVector targetLocation;
	// Interpolate to target rotation
	UFUNCTION()
	void RotTimerFunction();
	
	// Interpolate to target location
	UFUNCTION()
	void LocTimerFunction();
};
