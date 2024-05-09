// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSkill/RightHandAttack.h"
#include "Components/SphereComponent.h"
#include "RightHandAttack.h"

ARightHandAttack::ARightHandAttack()
{
    //PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("SkillMovement"));
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("AttackBoundary"));
    SphereComponent->SetupAttachment(RootComponent);

    RightHandAttackActorComponent = CreateDefaultSubobject<URightHandAttackComponent>(TEXT("RightHandAttackComponent"));
    RightHandAttackSceneComponent = CreateDefaultSubobject<URightHandAttackSceneComponent>(TEXT("RightHandAttackEffect"));
    
    RightHandAttackSceneComponent->SetupAttachment(RootComponent);
}

void ARightHandAttack::BeginPlay()
{
    // Throw Check With Montage

    SetActorLocation(FVector(-2000.f, 0.f, 100.f));
}

void ARightHandAttack::Tick(float DeltaTime)
{

}

void ARightHandAttack::SetSkillSpeed(float Speed)
{
    ProjectileMovement->MaxSpeed = Speed;
}
