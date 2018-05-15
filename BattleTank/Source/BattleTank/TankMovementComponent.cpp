// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"


void UTankMovementComponent::IntendMoveForward(float magnitude)
{
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("%s: magnitude = %f"),
		*GetName(),
		magnitude
	);
}


