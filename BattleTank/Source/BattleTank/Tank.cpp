// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Online/BuildPatchServices/Private/Core/Platform.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(
		FName("AimingComponent")
	);
}

void ATank::SetBarrelReference(UTankBarrel* barrel)
{
	Barrel = barrel;
	TankAimingComponent->SetBarrelReference(barrel);
}

void ATank::SetTurretReference(UTankTurret* turret)
{
	TankAimingComponent->SetTurretReference(turret);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector location)
{
	TankAimingComponent->AimAt(location, LaunchSpeed);
}

void ATank::Fire()
{
	if (!Barrel) { return; }

	const bool isReloaded =
		(FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
	{
		// Spawn a projectile
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation("Projectile"),
			Barrel->GetSocketRotation("Projectile")
			);

		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}