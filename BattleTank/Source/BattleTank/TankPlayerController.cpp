// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (!tank)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("(ATankPlayerController): No Tank is possessed!")
		)
	}
	else
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("(ATankPlayerController): %s is possessed!"),
			*tank->GetName()
		);
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}