// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "FollowCamera.h"
#include "RoomActor.generated.h"

UCLASS()
class BREAKINGTHECYCLE_API ARoomActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RoomCollision", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BaseRoomCollider;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RoomCollision|Left", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* LeftRoomCollider;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "RoomCollision|Right", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* RightRoomCollider;
	
public:	
	// Sets default values for this actor's properties
	ARoomActor();

	// Origin point for camera to be located
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoomCollision|Camera", meta = (AllowPrivateAccess = "true"))
		FVector OriginPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoomCollision|RotationSwing", meta = (AllowPrivateAccess = "true"))
		float SwingTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Reference to Player
	class APlayerCharacter* PlayerRef;

	// Reference to Follow Camera
	AFollowCamera* CameraRef;

	// Set if the player is in the room to control rotation
	bool bPlayerInRoom;

	// Set Camera to new Origin point
	UFUNCTION(BlueprintCallable)
		void ChangeCameraOrigin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	
	// Rotate Camera to left/right side of room. (Left - true, Right - False)
	UFUNCTION(BlueprintCallable)
		void AdjustCameraRotationLeft(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	// Rotate Camera to left/right side of room. (Left - true, Right - False)
	UFUNCTION(BlueprintCallable)
		void AdjustCameraRotationRight(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

};
