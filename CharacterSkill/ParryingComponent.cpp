// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSkill/ParryingComponent.h"
#include "GameData/DSGameSingleton.h"

UParryingComponent::UParryingComponent()
{
	SkillName = FName(TEXT("Parrying"));
}

void UParryingComponent::BeginPlay()
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