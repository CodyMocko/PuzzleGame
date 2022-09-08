// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MovedDistance);

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Move platform forward
	// Get current location
	FVector CurrentLocation = GetActorLocation();
	// Add vector to that location (likely a local variable)
	CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
	// Set the location
	SetActorLocation(CurrentLocation);

	// Send platform back if gone too far
		// Check how far we've moved
	float DistanceMoved = FVector::Distance(StartLocation, CurrentLocation);
		// Reverse direction if gone too far
	if (DistanceMoved > MovedDistance)
	{
		FString NameOfObject = GetName();
		float OverShoot = DistanceMoved - MovedDistance;
		UE_LOG(LogTemp, Warning, TEXT("Distance overshot: %f by %s"), OverShoot, *NameOfObject);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MovedDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}

