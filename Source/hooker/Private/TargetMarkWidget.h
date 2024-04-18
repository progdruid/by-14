// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hook.h"
#include "TargetMarkReceiver.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "TargetMarkWidget.generated.h"

/**
 * A widget to display the target mark
 * that the player aims to
 */
UCLASS()
class UTargetMarkWidget : public UUserWidget, public ITargetMarkReceiver
{
	GENERATED_BODY()
public:
	UTargetMarkWidget(const FObjectInitializer&);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	UImage* TargetMarkImage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHook> HookClass;

	virtual void SetTargetMarkPosition(FVector2D pos) override;
protected:
	virtual void NativeConstruct() override;
};
