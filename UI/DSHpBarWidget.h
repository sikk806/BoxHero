// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DSUserWidget.h"
#include "Interface/DSCharacterWidgetInterface.h"
#include "DSHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API UDSHpBarWidget : public UDSUserWidget
{
	GENERATED_BODY()
	
// Init Section
public:
	UDSHpBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

// Widget Setting Section
public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);
	void UpdateHpBarTxt(float NewCurrentHp);

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	TObjectPtr<class UTextBlock> HpInfo;

	UPROPERTY()
	float MaxHp;

};
