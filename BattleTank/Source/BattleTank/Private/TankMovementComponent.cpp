// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  // No need to call Super as we're replacing the functionality

  auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
  auto AIForwardIntention = MoveVelocity.GetSafeNormal();

  auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
  IntendMoveForward(ForwardThrow);

  auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
  IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  if (!ensure(LeftTrack && RightTrack)) { return; }
  LeftTrack->SetThrottle(Throw*10000000000);
  RightTrack->SetThrottle(Throw*10000000000);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
  if (!ensure(LeftTrack && RightTrack)) { return; }
  LeftTrack->SetThrottle(Throw*10000000000);
  RightTrack->SetThrottle(-Throw*10000000000);
}