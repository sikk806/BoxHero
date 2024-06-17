// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSkill/LaserSceneComponent.h"
#include "NiagaraComponent.h"

#include "TimerManager.h"
#include "Engine/World.h"

ULaserSceneComponent::ULaserSceneComponent()
{
    EnergyEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EnergyEffect"));
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EnergyEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DarkSorcery/Enemy/MidBoss/Skills/Laser/NS_Energy_1.NS_Energy_1'"));
    if(EnergyEffectRef.Object)
    {
        EnergyEffect->SetAsset(EnergyEffectRef.Object);
    }

    RayEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RayEffect"));
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> RayEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DarkSorcery/Enemy/MidBoss/Skills/Laser/NS_Ray_1.NS_Ray_1'"));
    if(RayEffectRef.Object)
    {
        RayEffect->SetAsset(RayEffectRef.Object);
    }

    HitEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HitEffect"));
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> HitEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/DarkSorcery/Enemy/MidBoss/Skills/Laser/NS_Hit_1.NS_Hit_1'"));
    if(HitEffectRef.Object)
    {
        HitEffect->SetAsset(HitEffectRef.Object);
    }

    EnergyEffect->SetupAttachment(GetAttachmentRoot());
    RayEffect->SetupAttachment(GetAttachmentRoot());
    HitEffect->SetupAttachment(GetAttachmentRoot());
}

void ULaserSceneComponent::BeginPlay()
{
    Super::BeginPlay();

    EnergyEffect->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
    EnergyEffect->SetActive(true);

    RayEffect->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
    RayEffect->SetRelativeScale3D(FVector(2.f, 1.f, 1.f));
    RayEffect->SetActive(false);

    HitEffect->SetRelativeLocation(FVector(3400.f, 0.f, 50.f));
    HitEffect->SetActive(false);

    GetWorld()->GetTimerManager().SetTimer(LaserTimer, this, &ULaserSceneComponent::EffectOn, 1.91f, false);
}
void ULaserSceneComponent::EffectOn()
{
    RayEffect->SetActive(true);
    HitEffect->SetActive(true);
}