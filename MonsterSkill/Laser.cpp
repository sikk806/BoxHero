// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSkill/Laser.h"
#include "MonsterSkill/LaserComponent.h"
#include "MonsterSkill/LaserSceneComponent.h"
#include "Character/DSCharacterPlayer.h"

#include "TimerManager.h"

ALaser::ALaser()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    LaserActorComponent = CreateDefaultSubobject<ULaserComponent>(TEXT("LaserComponent"));
    LaserSceneComponent = CreateDefaultSubobject<ULaserSceneComponent>(TEXT("LaserSceneComponent"));

    LaserSceneComponent->SetupAttachment(RootComponent);

    SetActorScale3D(FVector(0.1f));

}

void ALaser::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(DestroyTimer, this, &ALaser::DestroyActor, 4.95f, false);

}

void ALaser::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
