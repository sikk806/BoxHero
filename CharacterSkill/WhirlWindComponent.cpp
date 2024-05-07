// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/WhirlWindComponent.h"
#include "GameData/DSGameSingleton.h"

#include "NiagaraComponent.h"

UWhirlWindComponent::UWhirlWindComponent()
{
	SkillName = FName(TEXT("WhirlWind"));
}

void UWhirlWindComponent::BeginPlay()
{
	Super::BeginPlay();

	Skill = UDSGameSingleton::Get().GetCharacterSkillData(SkillName);

	SkillDescription = Skill.Description;
	Mana = Skill.Mana;
	Stamina = Skill.Stamina;
	Damage = Skill.Damage;
	HitCount = Skill.HitCount;
	CoolTime = Skill.CoolTime;
}
