// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/World.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{

  auto Time = GetWorld()->GetTimeSeconds();
  auto Name = GetName();
  UE_LOG(LogTemp, Warning, TEXT("%f: Intend move forward thrown: %f"), Time, Throw);
}

