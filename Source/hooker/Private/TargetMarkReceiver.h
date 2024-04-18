// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetMarkReceiver.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetMarkReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for an object to receive the info about the target mark
 */
class ITargetMarkReceiver
{
	GENERATED_BODY()

public:
	virtual void SetTargetMarkPosition(FVector2D pos);
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
