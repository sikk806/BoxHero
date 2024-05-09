// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSkill/Parrying.h"
#include "CharacterSkill/ParryingComponent.h"
#include "CharacterSkill/ParryingSceneComponent.h"

#include "Components/BoxComponent.h"

AParrying::AParrying()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ParryingBox"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->bHiddenInGame = false;

	ParryingActorComponent = CreateDefaultSubobject<UParryingComponent>(TEXT("ParryingComponent"));
	ParryingSceneComponent = CreateDefaultSubobject<UParryingSceneComponent>(TEXT("ParryingEffect"));	

	ParryingSceneComponent->SetupAttachment(RootComponent);

	//CheckTime = 0.f;
	UseMana = ParryingActorComponent->Mana;
}

void AParrying::BeginPlay()
{
    Super::BeginPlay();

	SetActorLocation(FVector(-2000.f, 0.f, 100.f));

	//ParryingSceneComponent->SetWorldLocation(BoxComponent->GetComponentLocation());
}

void AParrying::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
