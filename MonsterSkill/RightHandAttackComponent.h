// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSProjectileSkillComponent.h"
#include "RightHandAttackComponent.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API URightHandAttackComponent : public UDSProjectileSkillComponent
{
	GENERATED_BODY()

public:
	URightHandAttackComponent();

	virtual void BeginPlay() override;
};
