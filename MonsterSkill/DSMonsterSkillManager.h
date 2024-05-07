// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSMonsterSkillManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DARKSORCERY_API UDSMonsterSkillManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDSMonsterSkillManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION()
	virtual void ActivateSkill(FVector MonsterLocation, FRotator MonsterRotation, int SkillNum);

	UFUNCTION()
	virtual void DeActivateSkill(AActor *DestroySkill);
};
