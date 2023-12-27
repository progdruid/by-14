// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPawn.h"

// Sets default values
ALevelPawn::ALevelPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

void ALevelPawn::Tick(float _deltaTime)
{
	if (IsValid(LaunchedHook) && IsValid(PhysicsBody))
	{
		PhysicsBody->AddForce(LaunchedHook->GetPull(), NAME_None, true);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.f, FColor::Blue, LaunchedHook->GetPull().ToString());
	}
}

void ALevelPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALevelPawn::LaunchHook(TSubclassOf<AHook> _specifiedHook)
{
	UWorld* world = GetWorld();
	if (!world || !_specifiedHook)
		return;
	
	if (IsValid(LaunchedHook))
		RevokeHook();

	FTransform transform = GetActorTransform();

	//spawn
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	LaunchedHook = world->SpawnActor<AHook>(_specifiedHook, transform, spawnParams);

	//get mouse info
	FVector mousePosition, mouseDirection;
	bool found = world->GetFirstPlayerController()->DeprojectMousePositionToWorld(mousePosition, mouseDirection);
	if (!found)
		return;

	//calculate hook direction
	float t = -mousePosition.X / mouseDirection.X; // lerp factor
	FVector positionOnPlane = mousePosition + mouseDirection * t; // getting the point on the x = 0 plane
	positionOnPlane.X = 0.f;
	FVector hookDirection = positionOnPlane - transform.GetLocation();

	//set direction
	LaunchedHook->Setup(hookDirection, this);
}

void ALevelPawn::RevokeHook()
{
	if (!IsValid(LaunchedHook))
	{
		LaunchedHook = nullptr;
		return;
	}
	LaunchedHook->Destroy();
	LaunchedHook = nullptr;
}