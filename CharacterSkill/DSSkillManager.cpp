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
	SetMp(MaxMp);

	static ConstructorHelpers::FClassFinder<AWhirlWind> WhirlWindClassRef(TEXT("/Script/CoreUObject.Class'/Script/DarkSorcery.WhirlWind'"));
	if (WhirlWindClassRef.Class)
	{
		WhirlWindClass = WhirlWindClassRef.Class;
	}
}

// Called when the game starts
void UDSSkillManager::BeginPlay()
{
	Super::BeginPlay();

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
	NowMp = FMath::Clamp<float>(NowMp - NewMp, 0, MaxMp);
	OnMpChanged.Broadcast(NewMp);
}

void UDSSkillManager::ActivateSkill(FVector PlayerLocation, FRotator PlayerRotation)
{
	// DSMeleeSkillComponent need To Follow the Character (Ex. WhirlWind)
	//AWhirlWind *Skill;
	//float UseMana = Skill->WhirlWind->Mana;
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
