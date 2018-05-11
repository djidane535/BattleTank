// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"


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
	// TODO
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("%s is firing!"),
		*GetName()
	);

	if (!Barrel) { return; }

	// Spawn a projectile
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation("Projectile"),
		Barrel->GetSocketRotation("Projectile")
	);

	projectile->LaunchProjectile(LaunchSpeed);
}