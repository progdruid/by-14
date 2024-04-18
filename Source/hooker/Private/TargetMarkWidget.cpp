// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetMarkWidget.h"

#include "Components/CanvasPanelSlot.h"

UTargetMarkWidget::UTargetMarkWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
}

void UTargetMarkWidget::SetTargetMarkPosition(FVector2D pos)
{
	const auto slot = CastChecked<UCanvasPanelSlot>(TargetMarkImage->Slot);
	const FGeometry widgetGeometry = GetCachedGeometry();
	//might be very slow
	const auto uiPos = widgetGeometry.AbsoluteToLocal(pos);
	slot->SetPosition(uiPos);
}

void UTargetMarkWidget::NativeConstruct()
{
	if(!TargetMarkImage)
		return;
	//TargetMarkImage->SetVisibility(ESlateVisibility::Hidden);

	if (!HookClass)
		return;

	
}

