// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPlayerController.h"

ALevelPlayerController::ALevelPlayerController()
{
	
}

void ALevelPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!LevelPawn)
		return;
	
	const FVector pawnPosition = LevelPawn->GetActorTransform().GetLocation();
	
	//get mouse info
	FVector mousePosition, mouseDirection;
	const bool foundMouse = DeprojectMousePositionToWorld(mousePosition, mouseDirection);
	if (!foundMouse)
		return;

	//calculate hook direction
	const float t = -mousePosition.X / mouseDirection.X; // factor
	FVector positionOnPlane = mousePosition + mouseDirection * t; // getting the point on the x = 0 plane
	positionOnPlane.X = 0.f;
	Direction = positionOnPlane - pawnPosition;

	//raycast
	FHitResult result;
	FCollisionQueryParams query;
	query.AddIgnoredActor(LevelPawn);
	bool foundHit = GetWorld()->LineTraceSingleByChannel(
		result,
		pawnPosition,
		pawnPosition + Direction * 10000.f,
		ECC_Visibility,
		query);
	
	TargetPoint = result.Location;
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
	
	LevelPawn->LaunchHook(Direction);
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

