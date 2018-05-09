// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void UTankTurret::Turn(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);

	const float deltaYaw = relativeSpeed
		* MaxDegreesPerSecond
		* GetWorld()->DeltaTimeSeconds;

	const float rawNewYaw = RelativeRotation.Yaw + deltaYaw;

	SetRelativeRotation(FRotator(0, rawNewYaw, 0));
}


