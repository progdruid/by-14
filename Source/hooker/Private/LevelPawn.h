// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Hook.h"
#include "LevelPawn.generated.h"

UCLASS()
class ALevelPawn : public APawn
{
	GENERATED_BODY()

public:
	ALevelPawn();
	
	//field and properties

	
	//engine functions
protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//functions
	UFUNCTION(BlueprintCallable)
	void LaunchHook(TSubclassOf<AHook> _specifiedHook);

};
