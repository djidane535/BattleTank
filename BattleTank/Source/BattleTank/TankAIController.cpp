// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"


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


	ATank* playerTank = GetPlayerTank();
	if (!tank)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("(ATankAIController): No Player Tank can be found!")
		)
	}
	else
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("(ATankAIController): %s is the Player Tank!"),
			*playerTank->GetName()
		);
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { return nullptr;  }
	return Cast<ATank>(playerPawn);
}




