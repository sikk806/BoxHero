// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DSCharacterEnemy.h"
#include "DSCharacterNamed.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API ADSCharacterNamed : public ADSCharacterEnemy
{
	GENERATED_BODY()

public:
	ADSCharacterNamed();

	float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;
	
};
