// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual void AimAt(FVector location);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	virtual void Fire();

protected:
	UPROPERTY(BlueprintReadWrite)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0; // 400 m/s

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	double ReloadTimeInSeconds = 3.0;

	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr; // TODO - Remove
};
