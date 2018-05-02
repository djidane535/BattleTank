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

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	if (!GetControlledTank()) { return; }

	// Check if linetrace hit something
	FVector hitLocation; // Out parameter
	if (!GetSightRayHitLocation(hitLocation)) { return; }

	// Linetrace hit something
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Hit location: %s"),
		*hitLocation.ToString()
	);

	// Move turret and barrel towards this location.
	// TODO
}

bool ATankPlayerController::GetSightRayHitLocation(
	OUT FVector& out_hitLocation) const
{
	//	Get crosshair location
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(OUT viewportSizeX, OUT viewportSizeY);
	FVector2D screenLocation = FVector2D(
		FMath::RoundToZero(CrossHairXLocation * viewportSizeX),
		FMath::RoundToZero(CrossHairYLocation * viewportSizeY)
	);
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Screen location: %s"),
		*screenLocation.ToString()
	); // TODO


	FVector crossHairLocation; // TODO

	//	"De-project" the screen position of the crosshair to a world direction
	// TODO

	// Get an end location from crossairLocation along the de-projected direction
	FVector endPointLocation; // TODO

	//	Set object query parameters
	FCollisionObjectQueryParams objectQueryParams =
		FCollisionObjectQueryParams(); // TODO

	//	Set collision query parameters
	FCollisionQueryParams collisionQueryParams =
		FCollisionQueryParams(); // TODO

	//	Linetrace between crosshair and all objects
	FHitResult hit;
	bool hitIsFound = GetWorld()->LineTraceSingleByObjectType
	(
		OUT hit,
		crossHairLocation,
		endPointLocation,
		objectQueryParams,
		collisionQueryParams
	);

	//	Save hit location into out_hitLocation (if hit)
	out_hitLocation = hit.Location;

	//	Return true if hit, false else
	return hitIsFound;
}