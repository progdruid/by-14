// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
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
	if (HookState == EHookState::Flying)
	{
		AddActorWorldOffset(Direction * Speed * _deltaTime, true);

		if (!IsValid(PulledBody) || FVector::DistSquared(GetActorLocation(), PulledBody->GetActorLocation()) > RopeLength * RopeLength)
			Revoke();
	}
}

void AHook::Setup(FVector _direction, APawn* _pulledBody)
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
	HookState = EHookState::None;
	Destroy();
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.1, FColor::Yellow, FString("Revoked"));
}

void AHook::HandleSurfaceCollision(bool _isHookable)
{
	if (!_isHookable)
		Revoke();
	else if (HookState != EHookState::Clinged)
	{
		HookState = EHookState::Clinged;
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.1, FColor::Yellow, FString("Clinged"));
	}
}