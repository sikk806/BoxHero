// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/DSCharacterPlayer.h"
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

	// Character Stat
public:
	FORCEINLINE void SetPlayer(ADSCharacterPlayer* NewPlayer) { OwningPlayer = NewPlayer; }
	void UpdateHpBar(float NewCurrentHp);
	void UpdateMpBar(float NewCurrentMp);

protected:
	TObjectPtr<ADSCharacterPlayer> OwningPlayer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> Canvas;

	UPROPERTY()
	TObjectPtr<class UDSHpBarWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class UDSMpBarWidget> MpBar;

	float MaxHp;
	float MaxMp;

	// Character Skill
public:
	void SetSkillWidgetVisibility();
	
protected:
	UPROPERTY()
	TObjectPtr<class UDSSkillWidget> Skill;

	UPROPERTY()
	TObjectPtr<class UDSQuickSkillWidget> QuickSkill;

	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
