// Fill out your copyright notice in the Description page of Project Settings.

#include "Hook.h"
#include "Math/UnrealMathUtility.h" 

// Sets default values
AHook::AHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

float AHook::GetMaxHookableDistance() const
{
	return MaxHookableRopeLength;
}


// Called when the game starts or when spawned
void AHook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHook::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
	if (!ConnectedBody)
		Revoke();
	else if (HookState == EHookState::Flying)
	{
		const float distToSpawnSquared = FVector::DistSquared(spawnPosition, GetActorLocation());
		const float distToBodySquared = FVector::DistSquared(ConnectedBody->GetLocation(), GetActorLocation());
		if (FMath::Min(distToBodySquared, distToSpawnSquared) > MaxHookableRopeLength * MaxHookableRopeLength)
			Revoke();
		
		AddActorWorldOffset(Direction * HookFlyingSpeed * _deltaTime, true);
	}
	else if (HookState == EHookState::Clinged)
	{
		if (ConnectedBody->GetIsPullingRope())
			ApplyHandForce(_deltaTime);
		
		ApplyRopeForce(_deltaTime);
	}
}

void AHook::Setup(FVector _direction, TScriptInterface<IPullable> _pulledBody)
{
	if (!this)
		return;

	ConnectedBody = _pulledBody;
	
	Direction = _direction;
	Direction.Normalize();
	float angle = -FMath::RadiansToDegrees( FMath::Atan(Direction.Z / Direction.Y));;
	angle += 180.f * (Direction.Y < 0);

	spawnPosition = GetActorLocation();
	
	SetActorRotation(FRotator(0.f, 0.f, angle));
}

void AHook::Revoke()
{
	HookState = EHookState::None;
	Destroy();
}

void AHook::HandleSurfaceCollision(bool _isHookable)
{
	if (HookState != EHookState::Flying)
		return;
	else if (!_isHookable)
		Revoke();
	else if (HookState == EHookState::Flying && ConnectedBody)
	{
		HookState = EHookState::Clinged;
		ConnectedBody->ResetVelocity();
		FVector toHookVec = GetActorLocation() - ConnectedBody->GetLocation();
		CurrentRopeLength = toHookVec.Size();
		if (ConnectedBody->GetIsPullingRope())
		{
			toHookVec.Normalize();
			ConnectedBody->AddVelocity(toHookVec * InitPullVelocity);
		}
	}
}

void AHook::ApplyRopeForce(float _deltaTime)
{
	FVector impulse = GetActorLocation() - ConnectedBody->GetLocation();
	const float deltaDist = impulse.Size() - CurrentRopeLength;
	impulse.Normalize();
	impulse *= deltaDist * Stiffness * _deltaTime * (deltaDist > 0);
	ConnectedBody->AddVelocity(impulse);
}

void AHook::ApplyHandForce(float _deltaTime)
{
	FVector toHookVector = GetActorLocation() - ConnectedBody->GetLocation();
	const float dist = toHookVector.Size();
	CurrentRopeLength = FMath::Clamp(CurrentRopeLength, MinRopeLength, dist);
	toHookVector.Normalize();

	FVector vel = ConnectedBody->GetBodyVelocity();
	float speedToHook = vel.Size();
	vel.Normalize();
	speedToHook *= FVector::DotProduct(vel, toHookVector);
	if (speedToHook < MaxPullSpeed)
		ConnectedBody->AddVelocity(toHookVector * BodyPull * _deltaTime);
}