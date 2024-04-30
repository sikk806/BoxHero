// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSMeleeSkillComponent.h"
#include "ParryingComponent.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API UParryingComponent : public UDSMeleeSkillComponent
{
	GENERATED_BODY()
	
public:
	UParryingComponent();

	virtual void BeginPlay() override;
};
