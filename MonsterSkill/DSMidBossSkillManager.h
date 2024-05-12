// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterSkill/DSMonsterSkillManager.h"
#include "DSMidBossSkillManager.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API UDSMidBossSkillManager : public UDSMonsterSkillManager
{
	GENERATED_BODY()

public:
	UDSMidBossSkillManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SettingSkill(FName SkillName);
};