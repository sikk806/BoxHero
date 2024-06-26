// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSMonsterSkillManager.generated.h"

USTRUCT(BlueprintType)
struct FSkillAttackInfo
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	int32 SkillNo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	FName SkillName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	float AttackRangeWithRadius;

	FSkillAttackInfo() : SkillNo(0), SkillName(NAME_None), AttackRangeWithRadius(-1.f) {}

	FSkillAttackInfo(int32 Num, FName Name, float Range) : SkillNo(Num), SkillName(Name), AttackRangeWithRadius(Range) {}
};

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

protected:
	TArray<FSkillAttackInfo> MonsterSkillSet;
};
