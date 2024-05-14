// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkill.h"
#include "RightHandAttack.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API ARightHandAttack : public ADSCharacterSkill
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARightHandAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USphereComponent> SphereComponent;

	void SetSkillSpeed(float Speed);
	void Detach();

	UFUNCTION()
	void ActivateCollision(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	

	// Skill Option
public:
	float ThrowTime;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URightHandAttackComponent> RightHandAttackActorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URightHandAttackSceneComponent> RightHandAttackSceneComponent;

	FTimerHandle ThrowTimer;
	FTimerHandle DestroyTimer;
};
