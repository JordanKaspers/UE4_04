// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  if (!LeftTrack || !RightTrack) { return; }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
  // TODO prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
  if (!LeftTrack || !RightTrack) { return; }
  LeftTrack->SetThrottle(Throw*2);
  RightTrack->SetThrottle(-Throw*2);
  // TODO prevent double-speed due to dual control use
}
