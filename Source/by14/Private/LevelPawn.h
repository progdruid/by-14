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
	
	//field and properties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Main")
	TSubclassOf<AHook> SpecifiedHook;

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	AHook* LaunchedHook;
	UPROPERTY(Transient, BlueprintReadOnly)
	bool bIsPullingRope;

private:
	UPrimitiveComponent* PhysicsBody;

	//engine functions
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//interface functions
public:	
	UFUNCTION(BlueprintCallable)
	void LaunchHook(FVector _direction);
	UFUNCTION(BlueprintCallable)
	void RevokeHook();
	UFUNCTION(BlueprintCallable)
	void UpdateIsPulling (bool _isPulling);
	
	virtual void AddInstantaneousForce(FVector _force) override;
	virtual void AddVelocity(FVector _vel) override;
	virtual FVector GetLocation() override;
	virtual FVector GetBodyVelocity() override;
	virtual void ResetVelocity() override;
	virtual bool GetIsPullingRope() override;
};
