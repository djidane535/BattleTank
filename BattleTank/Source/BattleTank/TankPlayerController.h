// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#define OUT

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float deltaSeconds) override;

private:
	ATank* GetControlledTank() const;

	//	Moving the turrent and barrel towards the crosshair.
	void AimTowardsCrosshair() const;

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(OUT FVector& out_hitLocation) const;

	// TODO: should be same has defined for cross hair in PlayerUI
	const float CrossHairXLocation = 0.5;
	const float CrossHairYLocation = 1.0 / 3.0;
};
