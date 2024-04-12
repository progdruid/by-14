// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceCircleWidget.h"

UDistanceCircleWidget::UDistanceCircleWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UDistanceCircleWidget::NativeConstruct()
{
	if(!DistanceCircleImage)
		return;
	DistanceCircleImage->SetVisibility(ESlateVisibility::Hidden);

	if (!HookClass)
		return;
	float maxHookDist = HookClass.GetDefaultObject()->GetMaxHookableDistance();

	
}

