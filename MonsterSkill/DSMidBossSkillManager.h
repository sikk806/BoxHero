// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterSkill/DSMonsterSkillManager.h"
#include "DSMidBossSkillManager.generated.h"

UCLASS()
class DARKSORCERY_API UDSMidBossSkillManager : public UDSMonsterSkillManager
{
	GENERATED_BODY()

public:
	UDSMidBossSkillManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void SettingNextSkill();

	UFUNCTION()
	FORCEINLINE float GetNextSkillRange() { return NextSkillRange; }

	UFUNCTION()
	virtual void ActivateSkill(FVector MonsterLocation, FRotator MonsterRotation);

	UFUNCTION()
	virtual void DeActivateSkill(AActor *DestroySkill);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillSet", Meta = (AllowPrivateAccess = "true"))
	FName NextSkillName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillSet", Meta = (AllowPrivateAccess = "true"))
	float NextSkillRange;

	// Check ReWrite in Parent Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	AActor *SkillActor;

};