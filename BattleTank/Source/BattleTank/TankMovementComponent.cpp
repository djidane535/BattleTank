// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(
	UTankTrack* leftTrack,
	UTankTrack* rightTrack)
{
	if (!leftTrack || !rightTrack) { return; }

	LeftTrack = leftTrack;
	RightTrack = rightTrack;
}

void UTankMovementComponent::IntendMoveForward(float magnitude)
{
	if (!LeftTrack || !RightTrack) { return; }

	magnitude = FMath::Clamp<float>(magnitude, -1, 1);
	LeftTrack->SetThrottle(MaxSpeed *  magnitude);
	RightTrack->SetThrottle(MaxSpeed * magnitude);
}

void UTankMovementComponent::IntendTurnRight(float magnitude)
{
	if (!LeftTrack || !RightTrack) { return; }

	magnitude = FMath::Clamp<float>(magnitude, -1, 1);
	LeftTrack->SetThrottle(+MaxSpeed * magnitude);
	RightTrack->SetThrottle(-MaxSpeed * magnitude);
}

void UTankMovementComponent::RequestDirectMove(
	const FVector & MoveVelocity,
	bool bForceMaxSpeed)
{
	const FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	const FVector aiForwardIntention = MoveVelocity.GetSafeNormal();
	const float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	const float turnRightThrow = FVector::CrossProduct(tankForward, aiForwardIntention).Z;

	IntendMoveForward(forwardThrow);
	IntendTurnRight(turnRightThrow);
}