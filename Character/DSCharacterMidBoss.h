// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DSCharacterEnemy.h"
#include "DSCharacterMidBoss.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API ADSCharacterMidBoss : public ADSCharacterEnemy
{
	GENERATED_BODY()

	public:
	ADSCharacterMidBoss();

protected:
	virtual void BeginPlay() override;

	public:
	virtual void Tick(float DeltaTime) override;

	
	
};
