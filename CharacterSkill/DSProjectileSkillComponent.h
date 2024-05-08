// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkillComponent.h"
#include "DSProjectileSkillComponent.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API UDSProjectileSkillComponent : public UDSCharacterSkillComponent
{
	GENERATED_BODY()

public:
	UDSProjectileSkillComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	void SetProjectileMaxSpeed(float Speed);
};
