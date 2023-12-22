// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "Hook.generated.h"

UCLASS()
class AHook : public AActor
{
	GENERATED_BODY()
	
public:
	AHook();
	
	//fields and properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float Speed;
	UPROPERTY(Transient, BlueprintReadOnly)
	FVector Direction;
	UPROPERTY(Transient, BlueprintReadWrite)
	bool bIsFlying = true;

	//components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UShapeComponent* Collision;

	//engine functions
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float _deltaTime) override;

	//functions
	UFUNCTION(BlueprintCallable)
	void SetHookDirection(FVector _direction);
};
