// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"


void UTankTrack::SetThrottle(float throttle)
{
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("%s: throttle = %f"),
		*GetName(),
		throttle
	);

	const FVector forceApplied =
		throttle * TrackMaxDrivingForce * GetForwardVector();
	const FVector forceLocation =
		GetComponentLocation();
	auto tankRootComponent =
		Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRootComponent->AddForceAtLocation(forceApplied, forceLocation);
}
