// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkillSceneComponent.h"
#include "LaserSceneComponent.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API ULaserSceneComponent : public UDSCharacterSkillSceneComponent
{
	GENERATED_BODY()

public:
	ULaserSceneComponent();

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UNiagaraComponent> EnergyEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UNiagaraComponent> RayEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UNiagaraComponent> HitEffect;

	// Skill Option
protected:
	FTimerHandle LaserTimer;

	void EffectOn();
};
