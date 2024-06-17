// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkill.h"
#include "Laser.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API ALaser : public ADSCharacterSkill
{
	GENERATED_BODY()
public:
	ALaser();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	float LaserOnTime;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ULaserComponent> LaserActorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ULaserSceneComponent> LaserSceneComponent;

	// Skill Option
protected:
	FTimerHandle DestroyTimer;
	
};
