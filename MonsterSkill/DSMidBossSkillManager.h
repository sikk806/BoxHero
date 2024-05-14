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
	FORCEINLINE FName GetNextSkillName() { return NextSkillName; }

	UFUNCTION()
	FORCEINLINE float GetNextSkillRange() { return NextSkillRange; }

	UFUNCTION()
	void ActivateSkill(FVector MonsterLocation, FRotator MonsterRotation);

	UFUNCTION()
	void DeActivateSkill(AActor *DestroySkill);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillSet", Meta = (AllowPrivateAccess = "true"))
	FName NextSkillName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillSet", Meta = (AllowPrivateAccess = "true"))
	float NextSkillRange;

	// Check ReWrite in Parent Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	AActor *SkillActor;

	void CopySkill(FName SkillName, FVector MonsterLocation, FRotator MonsterRotation, int Copies);
};