// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DSCharacterBase.h"
#include "Interface/DSEnemyAIInterface.h"
#include "DSCharacterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API ADSCharacterEnemy : public ADSCharacterBase
{
	GENERATED_BODY()

public:
	ADSCharacterEnemy();

	FName EnemyName;

private:
	void AttackBegin();
	void AttackEnd(UAnimMontage *TargetMontage, bool IsProperlyEnded);
	void SetAttackCheckTimer();

	void SetDead() override;

	
	
};
