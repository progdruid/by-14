// Fill out your copyright notice in the Description page of Project Settings.


#include "Pullable.h"

// Add default functionality here for any IPullable functions that are not pure virtual.

void IPullable::AddInstantaneousForce(FVector _force)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f,
		FColor::Red, FString("Pulled, lol"));
}

void IPullable::AddInstantaneousVelocity(FVector _vel)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f,
		FColor::Red, FString("Added velocity, lol"));
}

FVector IPullable::GetLocation()
{
	return FVector(0, 0, 0);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f,
		FColor::Red, FString("Got location, lol"));
}

FVector IPullable::GetBodyVelocity()
{
	return FVector(0, 0, 0);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f,
		FColor::Red, FString("Got velocity, lol"));
}

void IPullable::ResetVelocity()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f,
		FColor::Red, FString("Reset velocity, lol"));
}

bool IPullable::GetIsPullingRope()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f,
		FColor::Red, FString("Got pulling rope, lol"));
	return false;
}