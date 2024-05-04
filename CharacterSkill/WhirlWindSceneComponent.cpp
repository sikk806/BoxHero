// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSkill/WhirlWindSceneComponent.h"
#include "NiagaraComponent.h"


UWhirlWindSceneComponent::UWhirlWindSceneComponent()
{
    SkillEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SkillEffect"));
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SkillEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DarkSorcery/Character/Skills/WhirlWind/NS_Warrior_Spin.NS_Warrior_Spin'"));
    if (SkillEffectRef.Object)
    {
        SkillEffect->SetAsset(SkillEffectRef.Object);
    }
    SkillEffect->SetupAttachment(GetAttachmentRoot());
}

void UWhirlWindSceneComponent::BeginPlay()
{
    Super::BeginPlay();
    
    SkillEffect->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
    SkillEffect->SetActive(true);
}
