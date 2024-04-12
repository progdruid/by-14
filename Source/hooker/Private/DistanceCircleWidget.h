// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hook.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "DistanceCircleWidget.generated.h"

/**
 * A widget to display the max distance
 * at which the player is able to throw the hook
 */
UCLASS()
class UDistanceCircleWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UDistanceCircleWidget(const FObjectInitializer&);

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* DistanceCircleImage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHook> HookClass;

};
