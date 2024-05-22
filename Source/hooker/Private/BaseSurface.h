// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BaseSurface.generated.h"

UCLASS()
class ABaseSurface : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSurface();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Main")
	FGameplayTagContainer GameplayTags;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
 	FGameplayTagContainer GetGameplayTagContainer() const;
};
