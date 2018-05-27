// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;


/**
 * Responsible for driving the tank tracks.
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float magnitude);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float magnitude);
	
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxSpeed = 1;

	UFUNCTION(BlueprintCallable)
	float GetMaxSpeed() const { return MaxSpeed; }

	void RequestDirectMove(
		const FVector & MoveVelocity,
		bool bForceMaxSpeed
	) override;

};
