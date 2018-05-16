// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Set throttle between -1 and 1
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float throttle);

private:
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	double TrackMaxDrivingForce = 1000.0 * 40000.0; // mass= 40 000, a = 10 m/s
};

