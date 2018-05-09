// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);

	const float deltaPitch = relativeSpeed
		* MaxDegreesPerSecond
		* GetWorld()->DeltaTimeSeconds;

	const auto rawNewPitch = FMath::Clamp<float>(
		RelativeRotation.Pitch + deltaPitch,
		MinElevationDegrees,
		MaxElevationDegrees
	);

	SetRelativeRotation(FRotator(rawNewPitch, 0, 0));
}
