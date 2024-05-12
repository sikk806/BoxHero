// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSMonsterSkillManager.generated.h"

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	int SkillNo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	FName SkillName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	float AttackRangeWithRadius;



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

	UFUNCTION()
	virtual void ActivateSkill(FVector MonsterLocation, FRotator MonsterRotation);

	UFUNCTION()
	virtual void DeActivateSkill(AActor *DestroySkill);

protected:
	TArray<FName> MonsterSkillSet;
	
};
