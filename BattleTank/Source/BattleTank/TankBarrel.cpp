// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float degreesPerSecond) const
{
	// Debug
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Elevate(%f)"),
		degreesPerSecond
	);
}
