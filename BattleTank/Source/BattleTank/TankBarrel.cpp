// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void UTankBarrel::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);

	const float deltaElevation = relativeSpeed
		* MaxDegressPerSecond
		* GetWorld()->DeltaTimeSeconds;

	const auto rawNewElevation = FMath::Clamp<float>(
		RelativeRotation.Pitch + deltaElevation,
		MinElevationDegrees,
		MaxElevationDegrees
	);

	SetRelativeRotation(FRotator(rawNewElevation, 0, 0));
}
