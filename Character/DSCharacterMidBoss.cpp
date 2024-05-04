// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DSCharacterMidBoss.h"
#include "DSCharacterMidBoss.h"

ADSCharacterMidBoss::ADSCharacterMidBoss()
{
    // Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

}

void ADSCharacterMidBoss::BeginPlay()
{

}

void ADSCharacterMidBoss::Tick(float DeltaTime)
{

}
