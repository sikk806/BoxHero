// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DSCharacterNamed.h"
#include "DSCharacterMidBoss.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API ADSCharacterMidBoss : public ADSCharacterNamed, public IDSEnemyAIInterface
{
	GENERATED_BODY()

public:
	ADSCharacterMidBoss();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// SkeletalMesh Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> SkeletalMeshDrill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> SkeletalMeshRing;

	// Attack
public:
	// Attack - Stat
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectedRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	// Attack AI
	FAICharacterAttackFinished OnAttackFinished;
	virtual void SetAttackDelegate(const FAICharacterAttackFinished &InOnAttackFinished) override;
	virtual void AttackByAI() override;
	void AttackBegin();
	void AttackEnd(UAnimMontage *TargetMontage, bool IsProperlyEnded);
	void NotifyActionEnd();

protected:
	float AIAttackRange;

	// Attack Effect
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDSMidBossSkillManager> SkillManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> SkillMontage;
};
