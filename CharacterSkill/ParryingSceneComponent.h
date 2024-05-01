// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkillSceneComponent.h"
#include "ParryingSceneComponent.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API UParryingSceneComponent : public UDSCharacterSkillSceneComponent
{
	GENERATED_BODY()

public:
	UParryingSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> SkillEffect;
};
