// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();

  auto ControlledTank = GetControlledTank();
  if (!ControlledTank)
  {
    ; UE_LOG(LogTemp, Error, TEXT("PlayerController not possesing a tank!"))
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
  }
}

void ATankPlayerController::Tick(float DeltaTime)
{
  Super::Tick( DeltaTime );
  AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
  if (!GetControlledTank())
  {
    return;
  }
  else
  {
    FVector HitLocation; // Out parameter
    if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
    {
      UE_LOG(LogTemp, Warning, TEXT("HitLocation = %s"),*HitLocation.ToString());

        // TODO Tell controlled tank to aim at this point

    }
  }
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
  OutHitLocation = FVector(1.0f);
  return true;
}