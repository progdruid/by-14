// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pullable.h"
#include "Components/ShapeComponent.h"
#include "Hook.generated.h"

UENUM(BlueprintType)
enum class EHookState : uint8
{
	None,
	Flying,
	Clinged
};

UCLASS()
class AHook : public AActor
{
	GENERATED_BODY()
	
public:
	AHook();

	//fields and properties
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float HookFlyingSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float MaxHookableRopeLength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float MinRopeLength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float Stiffness = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float RopePullSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float BodyPull = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	bool bUseNewPullSystem = false;
	UPROPERTY(Transient, BlueprintReadOnly)
	EHookState HookState = EHookState::Flying;
	UPROPERTY(Transient, BlueprintReadOnly)
	FVector Direction;
	UPROPERTY(Transient, BlueprintReadOnly)
	TScriptInterface<IPullable> ConnectedBody;
	UPROPERTY(Transient, BlueprintReadOnly)
	float CurrentRopeLength;

	//engine functions
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float _deltaTime) override;

	//functions
	UFUNCTION(BlueprintCallable)
	void Setup(FVector _direction, TScriptInterface<IPullable> _pulledBody);
	UFUNCTION(BlueprintCallable)
	void Revoke();
	UFUNCTION(BlueprintCallable)
	void HandleSurfaceCollision(bool _isHookable);

private:
	void ApplyRopeForce();
	void ApplyPullForce();
	void PullRope(float _deltaTime);
};
