// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

void UTankTrack::SetThrottle(float Throttle)
{
  auto Time = GetWorld()->GetTimeSeconds();
  auto Name = GetName();
  UE_LOG(LogTemp, Warning, TEXT("%f: %s throttle: %f"), Time, *Name, Throttle);

  // TODO Clamp actual throttle value so player can't over-drive

}

