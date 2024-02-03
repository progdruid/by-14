// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pullable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPullable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HOOKER_API IPullable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void AddInstantaneousForce(FVector _force);
	UFUNCTION()
	virtual void AddVelocity(FVector _vel);
	UFUNCTION()
	virtual FVector GetLocation();
	UFUNCTION()
	virtual FVector GetBodyVelocity();
	UFUNCTION()
	virtual void ResetVelocity();
	UFUNCTION()
	virtual bool GetIsPullingRope();
};
