// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// Get controlled tank
	Tank = Cast<ATank>(GetPawn());
	if (!Tank)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("(ATankAIController): No Tank is possessed!")
		);
		return;
	}

	// Get player tank
	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { PlayerTank = nullptr; }
	else { PlayerTank = Cast<ATank>(playerPawn); }
	if (!PlayerTank)
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
	if (AimTowardsPlayer()) { Tank->Fire(); }
}

bool ATankAIController::AimTowardsPlayer() const
{
	if (!Tank || !PlayerTank) { return false; }

	Tank->AimAt(PlayerTank->GetActorLocation());
	return true;
}
