// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Hook.h"

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
		AddActorWorldOffset(Direction * Speed * _deltaTime, true);

		if (FVector::DistSquared(GetActorLocation(), PulledBody.GetInterface()->GetLocation()) > RopeLength * RopeLength)
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
		PulledBody.GetInterface()->ToggleGravity(true);
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
		PulledBody.GetInterface()->ToggleGravity(false);
		HookedRopeLength = FVector::Distance(GetActorLocation(), PulledBody.GetInterface()->GetLocation());
	}
}

FVector AHook::GetPull()
{

	FVector pullAcc(0.f, 0.f, 0.f);
	if (PulledBody && HookState == EHookState::Clinged)
	{
		pullAcc = GetActorLocation() - PulledBody.GetInterface()->GetLocation();
		float dist = pullAcc.Size();
		float currentRopeLength = MinRopeLength + (HookedRopeLength - MinRopeLength) * PullTimer * HookedRopeLength / RopeLength / PullingTime;
		pullAcc *= (dist - currentRopeLength) / currentRopeLength * Stiffness * (dist - currentRopeLength > 0.f);
	}
	return pullAcc;
}