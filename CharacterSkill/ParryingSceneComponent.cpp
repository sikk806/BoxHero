// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/ParryingSceneComponent.h"
#include "NiagaraComponent.h"
#include "ParryingSceneComponent.h"


UParryingSceneComponent::UParryingSceneComponent()
{
    SkillEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SkillEffect"));
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SkillEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DarkSorcery/Character/Skills/Parrying/NS_Warrior_Parrying.NS_Warrior_Parrying'"));
    if (SkillEffectRef.Object)
    {
        SkillEffect->SetAsset(SkillEffectRef.Object);
    }
    SkillEffect->SetupAttachment(GetAttachmentRoot());
}
void UParryingSceneComponent::BeginPlay()
{
    Super::BeginPlay();
    
    SkillEffect->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
    SkillEffect->SetActive(true);
}