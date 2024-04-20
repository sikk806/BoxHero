// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/DSEnemyAIController.h"
#include "DSTrashMobAIController.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API ADSTrashMobAIController : public ADSEnemyAIController
{
	GENERATED_BODY()

public:
	ADSTrashMobAIController();

protected:
	virtual void OnPossess(APawn *InPawn) override;
	
};
