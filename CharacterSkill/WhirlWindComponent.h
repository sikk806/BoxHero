// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSMeleeSkillComponent.h"
#include "WhirlWindComponent.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API UWhirlWindComponent : public UDSMeleeSkillComponent
{
	GENERATED_BODY()

public:
	UWhirlWindComponent();

	virtual void BeginPlay() override;

	
};
