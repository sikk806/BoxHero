// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/DSSkillManager.h"

#include "CharacterSkill/DSMeleeSkillComponent.h"
#include "CharacterSkill/WhirlWind.h"
#include "DSSkillManager.h"

// Sets default values for this component's properties
UDSSkillManager::UDSSkillManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxMp = 100.f;

	static ConstructorHelpers::FObjectFinder<UBlueprint> WhirlWindRef(TEXT("/Game/DarkSorcery/Character/Skills/WhirlWind/WhirlWind.WhirlWind"));
	if (WhirlWindRef.Object)
	{
		WhirlWind = WhirlWindRef.Object;
	}

	bWantsInitializeComponent = true;
}

void UDSSkillManager::InitializeComponent()
{
	SetMp(MaxMp);
	NowMp = MaxMp;
}

// Called every frame
void UDSSkillManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SkillActor)
	{
		SkillActor->SetActorLocation(GetOwner()->GetActorLocation());
	}
}

void UDSSkillManager::SetMp(float NewMp)
{
	NowMp -= NewMp;
	OnMpChanged.Broadcast(NowMp);
}

void UDSSkillManager::ActivateSkill(FVector PlayerLocation, FRotator PlayerRotation)
{
	// DSMeleeSkillComponent need To Follow the Character (Ex. WhirlWind)
	AWhirlWind *Skill = GetWorld()->SpawnActor<AWhirlWind>(AWhirlWind::StaticClass(), PlayerLocation, PlayerRotation);
	if (Skill)
	{
		UDSMeleeSkillComponent *SkillComponent = Cast<UDSMeleeSkillComponent>(Skill->GetComponentByClass(UDSMeleeSkillComponent::StaticClass()));
		if (SkillComponent)
		{
			SkillActor = Skill;
			SkillActor->OnDestroyed.AddDynamic(this, &UDSSkillManager::DeActivateSkill);
		}
	}
}

void UDSSkillManager::DeActivateSkill(AActor *DestroySkill)
{
	SkillActor = nullptr;
}
