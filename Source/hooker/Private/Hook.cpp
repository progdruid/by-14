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

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->bEditableWhenInherited = true;
	Collision->SetSimulatePhysics(false);
	RootComponent = Collision;
	RootComponent->bEditableWhenInherited = true;
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
	if (!PulledBody)
		Revoke();
	else if (HookState == EHookState::Flying)
	{
		AddActorWorldOffset(Direction * FlyingSpeed * _deltaTime, true);

		if (FVector::DistSquared(GetActorLocation(), PulledBody->GetLocation()) > RopeLength * RopeLength)
			Revoke();
	}
	else if (HookState == EHookState::Clinged)
	{
		//decrease if greater than zero otherwise set to zero
		PullTimer = (PullTimer - _deltaTime) * (PullTimer > 0.f);
		if (PulledBody)
			PulledBody->AddPull(GetPull());
	}
}

void AHook::Setup(FVector _direction, TScriptInterface<IPullable> _pulledBody)
{
	PulledBody = _pulledBody;
	
	Direction = _direction;
	Direction.Normalize();

	float angle = -UKismetMathLibrary::DegAtan(Direction.Z / Direction.Y);
	angle += 180.f * (Direction.Y < 0);
	
	SetActorRotation(FRotator(0.f, 0.f, angle));
}

void AHook::Revoke()
{
	if (HookState == EHookState::Clinged && PulledBody)
		PulledBody->ToggleGravity(true);
	HookState = EHookState::None;
	Destroy();
}

void AHook::HandleSurfaceCollision(bool _isHookable)
{
	if (!_isHookable)
		Revoke();
	else if (HookState == EHookState::Flying && PulledBody)
	{
		HookState = EHookState::Clinged;
		PullTimer = PullingTime;
		PulledBody->ToggleGravity(false);
		PulledBody->ResetVelocity();
		HookedRopeLength = FVector::Distance(GetActorLocation(), PulledBody->GetLocation());
	}
}

FVector AHook::GetPull()
{

	FVector pullAcc(0.f, 0.f, 0.f);
	if (PulledBody && HookState == EHookState::Clinged)
	{
		pullAcc = GetActorLocation() - PulledBody->GetLocation();
		float dist = pullAcc.Size();
		float relativePullTime = PullTimer * HookedRopeLength / RopeLength;
		float currentRopeLength = MinRopeLength + (HookedRopeLength - MinRopeLength) * relativePullTime / PullingTime;
		pullAcc *= (dist - currentRopeLength) / currentRopeLength * Stiffness * (dist - currentRopeLength > 0.f);
	}
	return pullAcc;
}