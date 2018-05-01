// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (!tank)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("(ATankAIController): No Tank is possessed!")
		)
	}
	else
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("(ATankAIController): %s is possessed!"),
			*tank->GetName()
		);
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




