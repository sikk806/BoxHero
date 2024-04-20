// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/DSWhirlWind.h"
#include "GameData/DSGameSingleton.h"

UDSWhirlWind::UDSWhirlWind()
{
	
}

void UDSWhirlWind::BeginPlay()
{
	Super::BeginPlay();

	Skill = UDSGameSingleton::Get().GetCharacterSkillData(0);

	SkillName = Skill.Key;
	SkillDescription = Skill.Value.Description;
	Mana = Skill.Value.Mana;
	Stamina = Skill.Value.Stamina;
	Damage = Skill.Value.Damage;
	HitCount = Skill.Value.HitCount;
	CoolTime = Skill.Value.CoolTime;
}
