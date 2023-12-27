// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "Hook.h"
#include "LevelPawn.generated.h"

UCLASS()
class ALevelPawn : public APawn
{
	GENERATED_BODY()

public:
	ALevelPawn();
	
	//field and properties
private:
	UPROPERTY()
	AHook* LaunchedHook;
	UPROPERTY()
	UPrimitiveComponent* PhysicsBody;

	//engine functions
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float _deltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//functions
	UFUNCTION(BlueprintCallable)
	void LaunchHook(TSubclassOf<AHook> _specifiedHook);
	UFUNCTION(BlueprintCallable)
	void RevokeHook();
};
