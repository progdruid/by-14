// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DistanceCircleWidget.h"
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
	
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<UDistanceCircleWidget> DistanceCircleWidgetClass;

private:
	UDistanceCircleWidget* DistanceCircleWidget;
};
