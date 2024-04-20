// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSMeleeSkillComponent.h"
#include "DSWhirlWind.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API UDSWhirlWind : public UDSMeleeSkillComponent
{
	GENERATED_BODY()

public:
	UDSWhirlWind();

	virtual void BeginPlay() override;

	
};
