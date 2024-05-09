// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/DSEnemyAIController.h"
#include "DSMidBossAIController.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API ADSMidBossAIController : public ADSEnemyAIController
{
	GENERATED_BODY()

public:
	ADSMidBossAIController();

protected:
	virtual void OnPossess(APawn *InPawn) override;
};
