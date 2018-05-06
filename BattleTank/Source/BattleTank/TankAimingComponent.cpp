// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* barrel)
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

void UTankAimingComponent::AimAt(FVector location, float launchSpeed) const
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

	if (!isFeasible) { return; }

	// Get aim direction
	FVector aimDirection = launchVelocity.GetSafeNormal();
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("%s is aiming at %s"),
		*GetOwner()->GetName(),
		*aimDirection.ToString()
	);
}