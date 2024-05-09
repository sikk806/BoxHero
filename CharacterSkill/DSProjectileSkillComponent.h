// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkillComponent.h"
#include "DSProjectileSkillComponent.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API UDSProjectileSkillComponent : public UDSCharacterSkillComponent
{
	GENERATED_BODY()

public:
	UDSProjectileSkillComponent();

	float Speed;


};
