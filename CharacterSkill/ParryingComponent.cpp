// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSkill/ParryingComponent.h"
#include "GameData/DSGameSingleton.h"

#include "NiagaraComponent.h"

UParryingComponent::UParryingComponent()
{
    SkillEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SkillEffect"));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SkillEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DarkSorcery/Character/Skills/Parrying/NS_Warrior_Parrying.NS_Warrior_Parrying'"));
	if (SkillEffectRef.Object)
	{
		SkillEffect->SetAsset(SkillEffectRef.Object);
	}

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

    SkillEffect->SetActive(true);
}