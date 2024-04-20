// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DSUserWidget.h"
#include "Interface/DSCharacterWidgetInterface.h"
#include "DSMpBarWidget.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API UDSMpBarWidget : public UDSUserWidget
{
	GENERATED_BODY()

public:
	UDSMpBarWidget(const FObjectInitializer &ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	// Widget Setting Section
public:
	FORCEINLINE void SetMaxMp(float NewMaxMp) { MaxMp = NewMaxMp; }
	void UpdateMpBar(float NewCurrentMp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> MpProgressBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> MpInfo;

	UPROPERTY()
	float MaxMp;
};
