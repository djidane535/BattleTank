// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "CollisionQueryParams.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"


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
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	ATank* tank = GetControlledTank();
	if (!tank) { return; }

	// Check if linetrace hit something
	FVector hitLocation; // Out parameter
	if (!GetSightRayHitLocation(hitLocation)) { return; }

	// Move turret and barrel towards this location.
	tank->AimAt(hitLocation);
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(
	OUT FVector& out_hitLocation) const
{
	//	Get look direction
	FVector lookDirection;
	if (!GetLookDirection(OUT lookDirection))
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Unable to retrieve look direction")
		);
		return false;
	}

	// Get hit location
	if (!GetLookVectorHitLocation(
		lookDirection,
		OUT out_hitLocation)) { return false; }
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector& out_lookDirection) const
{
	//	Get crosshair screen location
	const FVector2D crossHairScreenLocation = GetCrossHairScreenLocation();

	//	Deproject the screen position of the crosshair to a world direction
	FVector cameraWorldLocation, crossHairWorldDirection;
	const bool deprojectIsFound = DeprojectScreenPositionToWorld(
		crossHairScreenLocation.X,
		crossHairScreenLocation.Y,
		OUT cameraWorldLocation,
		OUT crossHairWorldDirection);

	//	Return
	if (deprojectIsFound) {	out_lookDirection = crossHairWorldDirection; }
	return deprojectIsFound;
}

FVector2D ATankPlayerController::GetCrossHairScreenLocation() const
{
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(OUT viewportSizeX, OUT viewportSizeY);

	return FVector2D
	{
		FMath::RoundToZero(CrossHairLocationXRatio * viewportSizeX),
		FMath::RoundToZero(CrossHairLocationYRatio * viewportSizeY)
	};
}

bool ATankPlayerController::GetLookVectorHitLocation(
	FVector lookDirection,
	FVector& out_hitLocation) const
{
	//	Linetrace
	const FVector startPoint = PlayerCameraManager->GetCameraLocation();
	const FVector endPoint = startPoint + LineTraceRange * lookDirection;

	FHitResult hitResult;
	const bool isHit = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startPoint,
		endPoint,
		ECC_Visibility,
		FCollisionQueryParams
		(
			"",
			true,
			GetPawn()
		)
	);

	//	Return
	if (isHit) { out_hitLocation = hitResult.Location; }
	else { out_hitLocation = FVector(); }
	return isHit;
}
