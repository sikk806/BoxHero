// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/DSWhirlWind.h"
#include "GameData/DSGameSingleton.h"
#include "DSWhirlWind.h"

#include "NiagaraComponent.h"

UDSWhirlWind::UDSWhirlWind()
{
	SkillEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SkillEffect"));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SkillEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DarkSorcery/Character/Skills/WhirlWind/NS_Warrior_Spin.NS_Warrior_Spin'"));
	if (SkillEffectRef.Object)
	{
		SkillEffect->SetAsset(SkillEffectRef.Object);
	}
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

	SkillEffect->SetActive(true);
}
