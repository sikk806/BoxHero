// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API UDSHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UDSHUDWidget(const FObjectInitializer &ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void SettingHUD(float SetMaxHp, float SetMaxMp);
	void UpdateHpBar(float NewCurrentHp);
	void UpdateMpBar(float NewCurrentMp);

protected:
	UPROPERTY()
	TObjectPtr<class UDSHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UDSMpBarWidget> MpBar;

	float MaxHp;
	float MaxMp;
};
