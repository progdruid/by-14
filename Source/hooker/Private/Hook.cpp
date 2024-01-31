// Fill out your copyright notice in the Description page of Project Settings.

#include "Hook.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHook::AHook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
		AddActorWorldOffset(Direction * HookFlyingSpeed * _deltaTime, true);

		if (FVector::DistSquared(GetActorLocation(), ConnectedBody->GetLocation()) > MaxHookableRopeLength * MaxHookableRopeLength)
			Revoke();
	}
	else if (HookState == EHookState::Clinged)
	{
		if (ConnectedBody->GetIsPullingRope())
			ApplyHandForce();
		
		ApplyRopeForce();
	}
}

void AHook::Setup(FVector _direction, TScriptInterface<IPullable> _pulledBody)
{
	if (!this)
		return;

	ConnectedBody = _pulledBody;
	
	Direction = _direction;
	Direction.Normalize();

	float angle = -UKismetMathLibrary::DegAtan(Direction.Z / Direction.Y);
	angle += 180.f * (Direction.Y < 0);
	
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
			ConnectedBody->AddInstantaneousVelocity(toHookVec * InitPullVelocity);
		}
	}
}

void AHook::ApplyRopeForce()
{
	FVector force = GetActorLocation() - ConnectedBody->GetLocation();
	float dist = force.Size();
	force.Normalize();
	force *= (dist - CurrentRopeLength) * Stiffness * (dist - CurrentRopeLength > 0);
	ConnectedBody->AddInstantaneousForce(force);
}

void AHook::ApplyHandForce()
{
	FVector toHookVector = GetActorLocation() - ConnectedBody->GetLocation();
	float dist = toHookVector.Size();
	if (dist < CurrentRopeLength)
		CurrentRopeLength = dist;
	if (CurrentRopeLength < MinRopeLength)
		CurrentRopeLength = MinRopeLength;

	toHookVector.Normalize();

	FVector vel = ConnectedBody->GetBodyVelocity();
	float speedToHook = vel.Size();
	vel.Normalize();
	speedToHook *= FVector::DotProduct(vel, toHookVector);

	if (speedToHook < MaxPullSpeed)
		ConnectedBody->AddInstantaneousForce(toHookVector * BodyPull);
}