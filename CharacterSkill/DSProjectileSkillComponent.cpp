// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/DSProjectileSkillComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

UDSProjectileSkillComponent::UDSProjectileSkillComponent()
{
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void UDSProjectileSkillComponent::SetProjectileMaxSpeed(float Speed)
{
    ProjectileMovement->MaxSpeed = Speed;
}
