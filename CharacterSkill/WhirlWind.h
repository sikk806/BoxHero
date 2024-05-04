// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkill.h"
#include "WhirlWind.generated.h"

UCLASS()
class DARKSORCERY_API AWhirlWind : public ADSCharacterSkill
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWhirlWind();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SceneComponent;

// Skill Option
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWhirlWindComponent> WhirlWindActorComponent;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWhirlWindSceneComponent> WhirlWindSceneComponent;

	FTimerHandle DestroyTimer;

	// Damage Collision
	float CheckTime;
	
	const float Radius = 250.f;

};
