// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSSkillManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMpChangedDelegate, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DARKSORCERY_API UDSSkillManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDSSkillManager();

protected:
	virtual void InitializeComponent() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	FOnMpChangedDelegate OnMpChanged;

	// Character Skill Stat
public:
	FORCEINLINE float GetMaxMp() { return MaxMp; }
	FORCEINLINE float GetNowMp() { return NowMp; }
	
	void SetMp(float UseMp);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxMp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float NowMp;

	// Skills
public:
	UFUNCTION()
	virtual void ActivateSkill(FVector PlayerLocation, FRotator PlayerRotation);

	UFUNCTION()
	virtual void DeActivateSkill(AActor *DestroySkill);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	AActor *SkillActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	TObjectPtr<class UBlueprint> WhirlWind;

	
};
