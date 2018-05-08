// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrel)
{
	Barrel = barrel;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector location, float launchSpeed)
{
	if (!Barrel) { return; }

	// Calculation launch velocity
	const FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector launchVelocity;
	const FCollisionResponseParams collisionResponseParams;
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());

	const bool isFeasible = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT launchVelocity,
		startLocation,
		location,
		launchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		OUT collisionResponseParams,
		actorsToIgnore,
		false
	);

	if (isFeasible)
	{
		// Get aim direction
		FVector aimDirection = launchVelocity.GetSafeNormal();

		// Move barrel and turret towards aim direction
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// Compute angle distance between aimDirection and barrel rotation
	// (shortest angle, on XZ plane)
	FRotator barrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator diffRotator = aimRotator - barrelRotator;

	Barrel->Elevate(diffRotator.Pitch);
}