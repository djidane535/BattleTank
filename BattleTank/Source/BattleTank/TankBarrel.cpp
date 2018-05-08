// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void UTankBarrel::Elevate(float relativeSpeed) const
{
	// Debug
	auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("%f Elevate(%f)"),
		time,
		relativeSpeed
	);
}
