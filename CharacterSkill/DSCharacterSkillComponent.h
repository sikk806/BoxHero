// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/DSCharacterSkillData.h"
#include "DSCharacterSkillComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DARKSORCERY_API UDSCharacterSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDSCharacterSkillComponent();

	virtual void BeginPlay() override;

	// Skill Info.
public:
	TPair<FName, FDSCharacterSkillData> Skill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	FName SkillName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	FText SkillDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	float Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	float Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	int32 HitCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	float CoolTime;
};
