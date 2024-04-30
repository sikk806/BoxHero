// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSkill/Parrying.h"
#include "CharacterSkill/ParryingComponent.h"
#include "Parrying.h"

AParrying::AParrying()
{
    
	Parrying = CreateDefaultSubobject<UParryingComponent>(TEXT("ParryingComponent"));

	//CheckTime = 0.f;
	UseMana = Parrying->Mana;
}

void AParrying::BeginPlay()
{
    Super::BeginPlay();
}

void AParrying::Tick(float DeltaTime)
{
    Tick(DeltaTime);
}
