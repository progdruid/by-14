// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelHUD.h"

ALevelHUD::ALevelHUD()
{
	CreateWidgets();
}

void ALevelHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if(TargetMarkWidget)
		TargetMarkWidget->AddToViewport();
}

void ALevelHUD::DrawHUD()
{
	Super::DrawHUD();
}

TScriptInterface<ITargetMarkReceiver> ALevelHUD::GetMarkReceiver()
{
	if (!TargetMarkWidget)
		CreateWidgets();
	
	return TScriptInterface<ITargetMarkReceiver>(TargetMarkWidget);
}

void ALevelHUD::CreateWidgets()
{
	UWorld* world = GetWorld();

	if (!world)
		return;
		
	if (!TargetMarkWidget && TargetMarkWidgetClass)
		TargetMarkWidget = CreateWidget<UTargetMarkWidget>(world, TargetMarkWidgetClass);

	
}


