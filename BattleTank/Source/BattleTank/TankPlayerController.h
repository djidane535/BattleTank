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
	//	Moving the turrent and barrel towards the crosshair.
	void AimTowardsCrosshair() const;

	ATank* GetControlledTank() const;

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(OUT FVector& out_hitLocation) const;

	bool GetLookDirection(FVector& out_lookDirection) const;

	FVector2D GetCrossHairScreenLocation() const;

	bool GetLookVectorHitLocation(
		FVector lookDirection,
		FVector& out_hitLocation) const;

	// TODO: should be same has defined for cross hair in PlayerUI
	UPROPERTY(EditDefaultsOnly)
	float CrossHairLocationXRatio = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairLocationYRatio = 1.0 / 3.0;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0; // 10,000 m
};
