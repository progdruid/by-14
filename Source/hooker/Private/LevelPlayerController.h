// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetMarkReceiver.h"
#include "LevelPawn.h"
#include "GameFramework/PlayerController.h"
#include "LevelPlayerController.generated.h"

/**
 * A player controller for the main level
 */
UCLASS()
class ALevelPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALevelPlayerController();

private:
	ALevelPawn* LevelPawn;
	TScriptInterface<ITargetMarkReceiver> MarkReceiver;

	FVector Direction;
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	UFUNCTION(BlueprintCallable)
	void CallLaunch();
	UFUNCTION(BlueprintCallable)
	void CallRevoke();
	UFUNCTION(BlueprintCallable)
	void UpdatePullAxis (bool _isPulling);
};
