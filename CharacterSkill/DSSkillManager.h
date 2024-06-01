// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/DSQuickSlotUpdateInterface.h"
#include "DSSkillManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMpChangedDelegate, float);

struct FQuickSlotSkill
{
	FName SkillName;
	float Mana;
	float Damage;
	float CoolTime;

	FQuickSlotSkill() : SkillName(""), Mana(0.f), Damage(0.f), CoolTime(0.f) {}

	FQuickSlotSkill(FName NewSkillName, float ManaCost, float DamageValue, float CoolDown)
        : SkillName(NewSkillName), Mana(ManaCost), Damage(DamageValue), CoolTime(CoolDown) {}

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DARKSORCERY_API UDSSkillManager : public UActorComponent, public IDSQuickSlotUpdateInterface
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
	FORCEINLINE FName GetActivateSkillName(int SkillNum) { return QuickSkillName[SkillNum]; }
	FORCEINLINE FQuickSlotSkill GetActivateSkill(int SkillNum) { return QuickSkills[SkillNum]; }

	UFUNCTION()
	virtual void ActivateSkill(FVector PlayerLocation, FRotator PlayerRotation, int SkillNum);

	UFUNCTION()
	virtual void DeActivateSkill(AActor *DestroySkill);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill)
	//AActor *SkillActor;
	TObjectPtr<class ADSCharacterSkill> SkillActor;

	// For QuickSlot Skill
protected:
	TArray<FQuickSlotSkill> QuickSkills;
	TArray<FName> QuickSkillName;
	TArray<float> QuickCoolTime;

	virtual void AddQuickSlot(FName NewSkillName, int SkillNum) override;
	virtual void RemoveQuickSlot(int SkillNum) override;
};
