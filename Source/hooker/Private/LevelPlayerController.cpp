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

	LevelPawn->LaunchHook();
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

