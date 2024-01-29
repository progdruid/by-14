// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pullable.h"
#include "Components/PrimitiveComponent.h"
#include "Hook.h"
#include "LevelPawn.generated.h"

UCLASS()
class ALevelPawn : public APawn, public IPullable
{
	GENERATED_BODY()

public:
	ALevelPawn();
	
protected:
	//field and properties
	UPROPERTY(Transient, BlueprintReadWrite)
	bool bIsPullingRope;
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//functions
	UFUNCTION(BlueprintCallable)
	void LaunchHook(TSubclassOf<AHook> _specifiedHook);
	UFUNCTION(BlueprintCallable)
	void RevokeHook();
	UFUNCTION()
	virtual void AddInstantaneousForce(FVector _force) override;
	UFUNCTION()
	virtual FVector GetLocation() override;
	UFUNCTION()
	virtual FVector GetBodyVelocity() override;
	UFUNCTION()
	virtual void ToggleGravity(bool _bValue) override;
	UFUNCTION()
	virtual void ResetVelocity() override;
	UFUNCTION()
	virtual bool GetIsPullingRope() override;
};
