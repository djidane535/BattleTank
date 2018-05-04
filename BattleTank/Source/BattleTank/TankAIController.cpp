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
		);
		return;
	}

	ATank* playerTank = GetPlayerTank();
	if (!playerTank)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("(ATankAIController): No Player Tank can be found!")
		);
		return;
	}
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	AimTowardsPlayer();
}

void ATankAIController::AimTowardsPlayer() const
{
	ATank* tank = GetControlledTank();
	if (!tank) { return; }

	ATank* playerTank = GetPlayerTank();
	if (!playerTank) { return; }

	tank->AimAt(playerTank->GetActorLocation());
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




