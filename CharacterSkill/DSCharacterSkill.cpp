// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSkill/DSCharacterSkill.h"
#include "Character/DSCharacterPlayer.h"
#include "DSCharacterSkill.h"

// Sets default values
ADSCharacterSkill::ADSCharacterSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADSCharacterSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADSCharacterSkill::SetOwnerController(AController* NewOwner)
{
	OwnerController = NewOwner;
}

void ADSCharacterSkill::DestroyActor()
{
	Destroy();
}
