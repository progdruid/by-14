// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetMarkWidget.h"
#include "GameFramework/HUD.h"
#include "LevelHUD.generated.h"

/**
 * All the HUD on the level map
 */
UCLASS()
class ALevelHUD : public AHUD
{
	GENERATED_BODY()
public:
	ALevelHUD();
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UTargetMarkWidget> TargetMarkWidgetClass;

private:
	UTargetMarkWidget* TargetMarkWidget;
	
public:	
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	TScriptInterface<ITargetMarkReceiver> GetMarkReceiver();

private:
	void CreateWidgets();
};
