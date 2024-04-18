// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetMarkReceiver.h"

// Add default functionality here for any ITargetMarkReceiver functions that are not pure virtual.
void ITargetMarkReceiver::SetTargetMarkPosition(FVector2D pos)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f,
		FColor::Red, FString("Got this pos, lol: ") +
		pos.ToString());
}
