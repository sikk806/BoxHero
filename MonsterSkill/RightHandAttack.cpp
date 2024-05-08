// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSkill/RightHandAttack.h"
#include "Components/SphereComponent.h"

ARightHandAttack::ARightHandAttack()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("AttackBoundary"));
    SphereComponent->SetupAttachment(RootComponent);

    RightHandAttackActorComponent = CreateDefaultSubobject<URightHandAttackComponent>(TEXT("RightHandAttackComponent"));
    RightHandAttackSceneComponent = CreateDefaultSubobject<URightHandAttackSceneComponent>(TEXT("RightHandAttackEffect"));
    RightHandAttackSceneComponent->SetupAttachment(RootComponent);
}

void ARightHandAttack::BeginPlay()
{
    // Throw Check With Montage
}

void ARightHandAttack::Tick(float DeltaTime)
{

}
