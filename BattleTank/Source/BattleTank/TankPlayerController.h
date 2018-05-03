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

	bool GetLookDirection(FVector& out_lookDirection) const;
	FVector2D GetCrossHairScreenLocation() const;
	bool GetLookVectorHitLocation(
		FVector lookDirection,
		FVector& out_hitLocation) const;

	// TODO: should be same has defined for cross hair in PlayerUI
	const float CrossHairLocationXRatio = 0.5;
	const float CrossHairLocationYRatio = 1.0 / 3.0;
	const float LineTraceRange = 1000000.0;
};
