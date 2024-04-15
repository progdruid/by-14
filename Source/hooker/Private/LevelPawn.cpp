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
	
	PhysicsBody = CastChecked<UPrimitiveComponent>(RootComponent);
}

void ALevelPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RevokeHook();
}


void ALevelPawn::LaunchHook(FVector _direction)
{
	UWorld* world = GetWorld();
	if (!world || !SpecifiedHook || IsValid(LaunchedHook))
		return;
	
	//spawn
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	LaunchedHook = world->SpawnActor<AHook>(SpecifiedHook, GetActorTransform(), spawnParams);

	//set direction
	LaunchedHook->Setup(_direction, TScriptInterface<IPullable>(this));
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

void ALevelPawn::UpdateIsPulling(bool _isPulling)
{
	bIsPullingRope = _isPulling;
}

void ALevelPawn::AddInstantaneousForce(FVector _force)
{
	if (PhysicsBody)
		PhysicsBody->AddForce(_force, NAME_None, true);
}

void ALevelPawn::AddVelocity(FVector _vel)
{
	if (PhysicsBody)
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
	if (PhysicsBody)
		PhysicsBody->SetAllPhysicsLinearVelocity(FVector(0.f));
}

bool ALevelPawn::GetIsPullingRope()
{
	return bIsPullingRope;
}