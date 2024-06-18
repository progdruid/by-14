// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSurface.h"

// Sets default values
ABaseSurface::ABaseSurface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

//Called when the game starts or when spawned
void ABaseSurface::BeginPlay()
{
	Super::BeginPlay();
	
}

FGameplayTagContainer ABaseSurface::GetGameplayTagContainer() const
{
	return GameplayTags;
}

