// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPlayerController.h"

ALevelPlayerController::ALevelPlayerController()
{
	
}

void ALevelPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	LevelPawn = CastChecked<ALevelPawn>(InPawn);
}

void ALevelPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	
	LevelPawn = nullptr;
}

void ALevelPlayerController::CallLaunch()
{
	if (!LevelPawn)
		return;
	
	const FTransform transform = LevelPawn->GetActorTransform();

	//get mouse info
	FVector mousePosition, mouseDirection;
	const bool found = DeprojectMousePositionToWorld(mousePosition, mouseDirection);
	if (!found)
		return;

	//calculate hook direction
	const float t = -mousePosition.X / mouseDirection.X; // lerp factor
	FVector positionOnPlane = mousePosition + mouseDirection * t; // getting the point on the x = 0 plane
	positionOnPlane.X = 0.f;
	const FVector hookDirection = positionOnPlane - transform.GetLocation();
	
	LevelPawn->LaunchHook(hookDirection);
}

void ALevelPlayerController::CallRevoke()
{
	if (!LevelPawn)
		return;

	LevelPawn->RevokeHook();
}

void ALevelPlayerController::UpdatePullAxis(bool _isPulling)
{
	if (!LevelPawn)
		return;

	LevelPawn->UpdateIsPulling(_isPulling);
}

