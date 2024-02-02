// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pullable.h"
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
	float HookFlyingSpeed = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float MaxHookableRopeLength = 100000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float MinRopeLength = 10.;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float Stiffness = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float InitPullVelocity = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float BodyPull = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float MaxPullSpeed = 0.f;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	EHookState HookState = EHookState::Flying;
	UPROPERTY(Transient, BlueprintReadOnly)
	FVector Direction = FVector(0.f, 0.f, 0.f);
	UPROPERTY(Transient, BlueprintReadOnly)
	TScriptInterface<IPullable> ConnectedBody;
	UPROPERTY(Transient, BlueprintReadOnly)
	float CurrentRopeLength = 0.f;

	//engine functions
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
	void ApplyHandForce();
};
