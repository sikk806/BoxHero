// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DSEnemyAIController.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API ADSEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADSEnemyAIController();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn *InPawn) override;
	
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
