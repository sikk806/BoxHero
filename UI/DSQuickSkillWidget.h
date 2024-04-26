// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DSUserWidget.h"
#include "DSQuickSkillWidget.generated.h"

UCLASS()
class DARKSORCERY_API UDSQuickSkillWidget : public UDSUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeOnInitialized() override;
	virtual void Init(ADSCharacterPlayer *NewPlayer);

protected:
	TArray<UWidget *> Slots;

// Using The Quick Slot
protected:
	//virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
