// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelHUD.h"

ALevelHUD::ALevelHUD()
{
}

void ALevelHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (!DistanceCircleWidgetClass)
		return;
	
	DistanceCircleWidget = CreateWidget<UDistanceCircleWidget>(
		GetWorld(), DistanceCircleWidgetClass);

	if(!DistanceCircleWidget)
		return;
	
	DistanceCircleWidget->AddToViewport();
}

void ALevelHUD::DrawHUD()
{
	Super::DrawHUD();
}


