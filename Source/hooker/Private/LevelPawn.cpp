// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPawn.h"

// Sets default values
ALevelPawn::ALevelPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ALevelPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PhysicsBody = Cast<UPrimitiveComponent>(RootComponent);
}

void ALevelPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RevokeHook();
}

void ALevelPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALevelPawn::LaunchHook(TSubclassOf<AHook> _specifiedHook)
{
	UWorld* world = GetWorld();
	if (!world || !_specifiedHook || IsValid(LaunchedHook))
		return;

	const FTransform transform = GetActorTransform();

	//get mouse info
	FVector mousePosition, mouseDirection;
	const bool found = world->GetFirstPlayerController()->DeprojectMousePositionToWorld(mousePosition, mouseDirection);
	if (!found)
		return;

	//calculate hook direction
	float t = -mousePosition.X / mouseDirection.X; // lerp factor
	FVector positionOnPlane = mousePosition + mouseDirection * t; // getting the point on the x = 0 plane
	positionOnPlane.X = 0.f;
	const FVector hookDirection = positionOnPlane - transform.GetLocation();

	//spawn
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	LaunchedHook = world->SpawnActor<AHook>(_specifiedHook, transform, spawnParams);

	//set direction
	LaunchedHook->Setup(hookDirection, TScriptInterface<IPullable>(this));
}

void ALevelPawn::RevokeHook()
{
	if (!IsValid(LaunchedHook))
	{
		LaunchedHook = nullptr;
		return;
	}
	LaunchedHook->Revoke();
	LaunchedHook = nullptr;
}

void ALevelPawn::AddInstantaneousForce(FVector _force)
{
	PhysicsBody->AddForce(_force, NAME_None, true);
}

void ALevelPawn::AddVelocity(FVector _vel)
{
	PhysicsBody->AddImpulse(_vel, NAME_None, true);
}

FVector ALevelPawn::GetLocation()
{
	return GetActorLocation();
}

FVector ALevelPawn::GetBodyVelocity()
{
	return GetVelocity();
}

void ALevelPawn::ResetVelocity()
{
	PhysicsBody->SetAllPhysicsLinearVelocity(FVector(0.f));
}

bool ALevelPawn::GetIsPullingRope()
{
	return bIsPullingRope;
}