// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DSCharacterEnemy.h"
#include "Interface/DSEnemyAIInterface.h"
#include "Interface/DSWeaponCollisionInterface.h"
#include "DSCharacterTrashMob.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API ADSCharacterTrashMob : public ADSCharacterEnemy, public IDSEnemyAIInterface, public IDSWeaponCollisionInterface
{
	GENERATED_BODY()

public:
	ADSCharacterTrashMob();

protected:
	virtual void BeginPlay() override;

// Attack
public:
	// Attack - Stat
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectedRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	// Attack AI
	virtual void SetAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	FAICharacterAttackFinished OnAttackFinished;
	void AttackBegin();
	void AttackEnd(UAnimMontage *TargetMontage, bool IsProperlyEnded);
	void NotifyActionEnd();

	// Attack - Collision
	virtual void SettingWeaponCollision() override;
	
	UFUNCTION()
	void CallOnHitDelegate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	
// Anim Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> AttackMontage;

// Item Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> SkeletalMeshWeapon;

};
