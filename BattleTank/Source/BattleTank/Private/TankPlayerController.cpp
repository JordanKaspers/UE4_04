// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!ensure(AimingComponent)) { return; }
  FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
  Super::Tick( DeltaTime );
  AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!ensure(AimingComponent)) { return; }
  else
  {
    FVector HitLocation; // Out parameter
    if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
    {
      AimingComponent->AimAt(HitLocation);
    }
  }
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
  // Find the crosshair position in pixel coordinates
  int32 ViewportSizeX, ViewportSizeY;
  GetViewportSize(ViewportSizeX, ViewportSizeY);
  FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

  // "De-project" the screen position of the crosshair to a world direction
  FVector LookDirection;
  if (GetLookDirection(ScreenLocation, LookDirection))
  {
    // Line-trace along that LookDirection, and see what we hit (up to a maximum range)
    GetLookVectorHitLocation(LookDirection, OutHitLocation);
  }

  return true;
}

// LineTraceSingleByChannel
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
  FHitResult HitResult;
  auto StartLocation = PlayerCameraManager->GetCameraLocation();
  auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
  if(GetWorld()->LineTraceSingleByChannel(
      HitResult, 
      StartLocation, 
      EndLocation, 
      ECollisionChannel::ECC_Visibility))
  {
    OutHitLocation = HitResult.Location;
    return true;
  }
  OutHitLocation = FVector(0);
  return false; // Line trace didn't succeed


  //return GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::)
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
  FVector CameraWorldLocation; // To be discarded
  FVector WorldDirection;
  return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
