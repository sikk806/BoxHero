// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkillSceneComponent.h"
#include "RightHandAttackSceneComponent.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API URightHandAttackSceneComponent : public UDSCharacterSkillSceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> SkillEffect;
};
