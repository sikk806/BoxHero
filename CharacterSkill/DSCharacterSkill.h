// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSCharacterSkill.generated.h"

UCLASS()
class DARKSORCERY_API ADSCharacterSkill : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADSCharacterSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetMana(float Mana) { UseMana = Mana; }
	FORCEINLINE float GetMana() { return UseMana; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	void SetMovementSpeed(float Speed);

	// Skill Option
protected:
	float UseMana;

	void DestroyActor();
};
