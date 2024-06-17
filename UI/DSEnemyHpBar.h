// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DSUserWidget.h"
#include "DSEnemyHpBar.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API UDSEnemyHpBar : public UDSUserWidget
{
	GENERATED_BODY()

	// Init Section
public:
	UDSEnemyHpBar(const FObjectInitializer &ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	// Widget Setting Section
public:
	void SetMaxHp(float NewMaxHp);
	void UpdateHpBar(float NewCurrentHp);
	void SetEnemyText(FName Name);

protected:
	UPROPERTY()
	TObjectPtr<class UDSHpBarWidget> EnemyHpWidget;

	UPROPERTY()
	TObjectPtr<class UTextBlock> EnemyName;

	UPROPERTY()
	TObjectPtr<class UTextBlock> EnemyHpText;

	UPROPERTY()
	float MaxHp;

	UPROPERTY()
	float NowHp;
};
