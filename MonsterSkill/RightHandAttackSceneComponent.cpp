// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSkill/RightHandAttackSceneComponent.h"
#include "NiagaraComponent.h"

URightHandAttackSceneComponent::URightHandAttackSceneComponent()
{
    SkillEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SkillEffect"));
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SkillEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DarkSorcery/Enemy/MidBoss/Skills/RightHandAttack/NS_ROCKET_Trail.NS_ROCKET_Trail'"));
    if(SkillEffectRef.Object)
    {
        SkillEffect->SetAsset(SkillEffectRef.Object);
    }
    SkillEffect->SetupAttachment(GetAttachmentRoot());
}

void URightHandAttackSceneComponent::BeginPlay()
{
    Super::BeginPlay();
    
    SkillEffect->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
    SkillEffect->SetActive(true);
}