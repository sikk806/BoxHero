// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DSUserWidget.h"
#include "DSSkillWidget.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API UDSSkillWidget : public UDSUserWidget
{
	GENERATED_BODY()

public:
	virtual void Init(ADSCharacterPlayer* NewPlayer);

protected:
	virtual void NativeConstruct() override;

protected:
	TArray<UWidget *> Slots;
};
