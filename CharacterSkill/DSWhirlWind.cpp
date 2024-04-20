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

	SkillName = FName(TEXT("WhirlWind"));
}

void UDSWhirlWind::BeginPlay()
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
